
#include "aes.h"

/*****************************************************************************/
/* Private functions:                                                        */
/*****************************************************************************/
static uint8_t getSBoxValue(uint8_t num)
{
	return sbox[num];
}

static uint8_t getSBoxInvert(uint8_t num)
{
	return rsbox[num];
}

// This function produces Nb(Nr+1) round keys. The round keys are used in each round to decrypt the states.
static void KeyExpansion(void)
{
	uint32_t i, j, k;
	uint8_t tempa[4]; // Used for the column/row operations

					  // The first round key is the key itself.
	for (i = 0; i < Nk; ++i)
	{
		RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
		RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
		RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
		RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];
	}

	// All other round keys are found from the previous round keys.
	for (; (i < (Nb * (Nr + 1))); ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			tempa[j] = RoundKey[(i - 1) * 4 + j];
		}
		if (i % Nk == 0)
		{
			// This function rotates the 4 bytes in a word to the left once.
			// [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

			// Function RotWord()
			{
				k = tempa[0];
				tempa[0] = tempa[1];
				tempa[1] = tempa[2];
				tempa[2] = tempa[3];
				tempa[3] = k;
			}

			// SubWord() is a function that takes a four-byte input word and
			// applies the S-box to each of the four bytes to produce an output word.

			// Function Subword()
			{
				tempa[0] = getSBoxValue(tempa[0]);
				tempa[1] = getSBoxValue(tempa[1]);
				tempa[2] = getSBoxValue(tempa[2]);
				tempa[3] = getSBoxValue(tempa[3]);
			}

			tempa[0] = tempa[0] ^ Rcon[i / Nk];
		}
		else if (Nk > 6 && i % Nk == 4)
		{
			// Function Subword()
			{
				tempa[0] = getSBoxValue(tempa[0]);
				tempa[1] = getSBoxValue(tempa[1]);
				tempa[2] = getSBoxValue(tempa[2]);
				tempa[3] = getSBoxValue(tempa[3]);
			}
		}
		RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ tempa[0];
		RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ tempa[1];
		RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ tempa[2];
		RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ tempa[3];
	}
}

// This function adds the round key to state.
// The round key is added to the state by an XOR function.
static void AddRoundKey(uint8_t round)
{
	uint8_t i, j;
	for (i = 0;i<4;++i)
	{
		for (j = 0; j < 4; ++j)
		{
			(*state)[i][j] ^= RoundKey[round * Nb * 4 + i * Nb + j];
		}
	}
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void SubBytes(void)
{
	uint8_t i, j;
	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			(*state)[j][i] = getSBoxValue((*state)[j][i]);
		}
	}
}

// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
static void ShiftRows(void)
{
	uint8_t temp;

	// Rotate first row 1 columns to left
	temp = (*state)[0][1];
	(*state)[0][1] = (*state)[1][1];
	(*state)[1][1] = (*state)[2][1];
	(*state)[2][1] = (*state)[3][1];
	(*state)[3][1] = temp;

	// Rotate second row 2 columns to left
	temp = (*state)[0][2];
	(*state)[0][2] = (*state)[2][2];
	(*state)[2][2] = temp;

	temp = (*state)[1][2];
	(*state)[1][2] = (*state)[3][2];
	(*state)[3][2] = temp;

	// Rotate third row 3 columns to left
	temp = (*state)[0][3];
	(*state)[0][3] = (*state)[3][3];
	(*state)[3][3] = (*state)[2][3];
	(*state)[2][3] = (*state)[1][3];
	(*state)[1][3] = temp;
}

static uint8_t xtime(uint8_t x)
{
	return ((x << 1) ^ (((x >> 7) & 1) * 0x1b));
}

// MixColumns function mixes the columns of the state matrix
static void MixColumns(void)
{
	uint8_t i;
	uint8_t Tmp, Tm, t;
	for (i = 0; i < 4; ++i)
	{
		t = (*state)[i][0];
		Tmp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i][3];
		Tm = (*state)[i][0] ^ (*state)[i][1]; Tm = xtime(Tm);  (*state)[i][0] ^= Tm ^ Tmp;
		Tm = (*state)[i][1] ^ (*state)[i][2]; Tm = xtime(Tm);  (*state)[i][1] ^= Tm ^ Tmp;
		Tm = (*state)[i][2] ^ (*state)[i][3]; Tm = xtime(Tm);  (*state)[i][2] ^= Tm ^ Tmp;
		Tm = (*state)[i][3] ^ t;        Tm = xtime(Tm);  (*state)[i][3] ^= Tm ^ Tmp;
	}
}

// Multiply is used to multiply numbers in the field GF(2^8)
#if MULTIPLY_AS_A_FUNCTION
static uint8_t Multiply(uint8_t x, uint8_t y)
{
	return (((y & 1) * x) ^
		((y >> 1 & 1) * xtime(x)) ^
		((y >> 2 & 1) * xtime(xtime(x))) ^
		((y >> 3 & 1) * xtime(xtime(xtime(x)))) ^
		((y >> 4 & 1) * xtime(xtime(xtime(xtime(x))))));
}
#else
#define Multiply(x, y)                                \
      (  ((y & 1) * x) ^                              \
      ((y>>1 & 1) * xtime(x)) ^                       \
      ((y>>2 & 1) * xtime(xtime(x))) ^                \
      ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^         \
      ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))   \

#endif

// MixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the inexperienced.
// Please use the references to gain more information.
static void InvMixColumns(void)
{
	int i;
	uint8_t a, b, c, d;
	for (i = 0;i<4;++i)
	{
		a = (*state)[i][0];
		b = (*state)[i][1];
		c = (*state)[i][2];
		d = (*state)[i][3];

		(*state)[i][0] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		(*state)[i][1] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		(*state)[i][2] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		(*state)[i][3] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	}
}


// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void InvSubBytes(void)
{
	uint8_t i, j;
	for (i = 0;i<4;++i)
	{
		for (j = 0;j<4;++j)
		{
			(*state)[j][i] = getSBoxInvert((*state)[j][i]);
		}
	}
}

static void InvShiftRows(void)
{
	uint8_t temp;

	// Rotate first row 1 columns to right
	temp = (*state)[3][1];
	(*state)[3][1] = (*state)[2][1];
	(*state)[2][1] = (*state)[1][1];
	(*state)[1][1] = (*state)[0][1];
	(*state)[0][1] = temp;

	// Rotate second row 2 columns to right
	temp = (*state)[0][2];
	(*state)[0][2] = (*state)[2][2];
	(*state)[2][2] = temp;

	temp = (*state)[1][2];
	(*state)[1][2] = (*state)[3][2];
	(*state)[3][2] = temp;

	// Rotate third row 3 columns to right
	temp = (*state)[0][3];
	(*state)[0][3] = (*state)[1][3];
	(*state)[1][3] = (*state)[2][3];
	(*state)[2][3] = (*state)[3][3];
	(*state)[3][3] = temp;
}


// Cipher is the main function that encrypts the PlainText.
static void Cipher(void)
{
	uint8_t round = 0;

	// Add the First round key to the state before starting the rounds.
	AddRoundKey(0);

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for (round = 1; round < Nr; ++round)
	{
		SubBytes();
		ShiftRows();
		MixColumns();
		AddRoundKey(round);
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	SubBytes();
	ShiftRows();
	AddRoundKey(Nr);
}

static void InvCipher(void)
{
	uint8_t round = 0;

	// Add the First round key to the state before starting the rounds.
	AddRoundKey(Nr);

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for (round = Nr - 1;round>0;round--)
	{
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(round);
		InvMixColumns();
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	InvShiftRows();
	InvSubBytes();
	AddRoundKey(0);
}

static void BlockCopy(uint8_t* output, const uint8_t* input)
{
	uint8_t i;
	for (i = 0;i<KEYLEN;++i)
	{
		output[i] = input[i];
	}
}



/*****************************************************************************/
/* Public functions:                                                         */
/*****************************************************************************/
#if defined(ECB) && ECB


void AES128_ECB_encrypt(const uint8_t* input, const uint8_t* key, uint8_t* output)
{
	// Copy input to output, and work in-memory on output
	BlockCopy(output, input);
	state = (state_t*)output;

	Key = key;
	KeyExpansion();

	// The next function call encrypts the PlainText with the Key using AES algorithm.
	Cipher();
}


/*AES_128加密数据（字符串）
*input:输入数据 -- unsigned char*
*key:密钥（16字节）-- unsigned char*
*output:输出数据 -- unsigned char*
*
*/
void all_AES128_ECB_encrypt(const uint8_t* input, const uint8_t* key, uint8_t* output)
{

	AES128_ECB_encrypt(input, key, output);//加密，plain_text为明文，key为密钥，buf为加密后数据

	if (strlen(input) > 16)
		AES128_ECB_encrypt(&input[16], key, &output[16]);//加密，plain_text为明文，key为密钥，buf为加密后数据

	if (strlen(input) > 32)
		AES128_ECB_encrypt(&input[32], key, &output[32]);//加密，plain_text为明文，key为密钥，buf为加密后数据

	if (strlen(input) > 48)
		AES128_ECB_encrypt(&input[48], key, &output[48]);//加密，plain_text为明文，key为密钥，buf为加密后数据

	if (strlen(input) > 64)
		AES128_ECB_encrypt(&input[64], key, &output[64]);//加密，plain_text为明文，key为密钥，buf为加密后数据

	if (strlen(input) > 80)
		AES128_ECB_encrypt(&input[80], key, &output[80]);//加密，plain_text为明文，key为密钥，buf为加密后数据


	if (strlen(input) > 96)
		AES128_ECB_encrypt(&input[96], key, &output[96]);//加密，plain_text为明文，key为密钥，buf为加密后数据

	if (strlen(input) > 112)
		AES128_ECB_encrypt(&input[112], key, &output[112]);//加密，plain_text为明文，key为密钥，buf为加密后数据

}


void AES128_ECB_decrypt(const uint8_t* input, const uint8_t* key, uint8_t *output)
{
	// Copy input to output, and work in-memory on output
	BlockCopy(output, input);
	state = (state_t*)output;

	// The KeyExpansion routine must be called before encryption.
	Key = key;
	KeyExpansion();

	InvCipher();
}

/*AES_128解密数据（字符串）
*input:输入数据 -- unsigned char*
*key:密钥（16字节）-- unsigned char*
*output:输出数据 -- unsigned char*
*
*/
void all_AES128_ECB_decrypt(const uint8_t* input, const uint8_t* key, uint8_t *output)
{

	AES128_ECB_decrypt(input, key, output);//解密，buf是加密数据，key是密钥，buf2是解密后数据


	if (strlen(input) > 16)
		AES128_ECB_decrypt(&input[16], key, &output[16]);//解密，buf是加密数据，key是密钥，buf2是解密后数据

	if (strlen(input) > 32)
		AES128_ECB_decrypt(&input[32], key, &output[32]);//解密，buf是加密数据，key是密钥，buf2是解密后数据

	if (strlen(input) > 48)
		AES128_ECB_decrypt(&input[48], key, &output[48]);//解密，buf是加密数据，key是密钥，buf2是解密后数据


	if (strlen(input) > 64)
		AES128_ECB_decrypt(&input[64], key, &output[64]);//加密，plain_text为明文，key为密钥，buf为加密后数据

	if (strlen(input) > 80)
		AES128_ECB_decrypt(&input[80], key, &output[80]);//加密，plain_text为明文，key为密钥，buf为加密后数据


	if (strlen(input) > 96)
		AES128_ECB_decrypt(&input[96], key, &output[96]);//加密，plain_text为明文，key为密钥，buf为加密后数据

	if (strlen(input) > 112)
		AES128_ECB_decrypt(&input[112], key, &output[112]);//加密，plain_text为明文，key为密钥，buf为加密后数据


}
#endif // #if defined(ECB) && ECB



#if defined(CBC) && CBC


static void XorWithIv(uint8_t* buf)
{
	uint8_t i;
	for (i = 0; i < KEYLEN; ++i)
	{
		buf[i] ^= Iv[i];
	}
}

void AES128_CBC_encrypt_buffer(uint8_t* output, uint8_t* input, uint32_t length, const uint8_t* key, const uint8_t* iv)
{
	uintptr_t i;
	uint8_t remainders = length % KEYLEN; /* Remaining bytes in the last non-full block */

	BlockCopy(output, input);
	state = (state_t*)output;

	// Skip the key expansion if key is passed as 0
	if (0 != key)
	{
		Key = key;
		KeyExpansion();
	}

	if (iv != 0)
	{
		Iv = (uint8_t*)iv;
	}

	for (i = 0; i < length; i += KEYLEN)
	{
		XorWithIv(input);
		BlockCopy(output, input);
		state = (state_t*)output;
		Cipher();
		Iv = output;
		input += KEYLEN;
		output += KEYLEN;
	}

	if (remainders)
	{
		BlockCopy(output, input);
		memset(output + remainders, 0, KEYLEN - remainders); /* add 0-padding */
		state = (state_t*)output;
		Cipher();
	}
}

void AES128_CBC_decrypt_buffer(uint8_t* output, uint8_t* input, uint32_t length, const uint8_t* key, const uint8_t* iv)
{
	uintptr_t i;
	uint8_t remainders = length % KEYLEN; /* Remaining bytes in the last non-full block */

	BlockCopy(output, input);
	state = (state_t*)output;

	// Skip the key expansion if key is passed as 0
	if (0 != key)
	{
		Key = key;
		KeyExpansion();
	}

	// If iv is passed as 0, we continue to encrypt without re-setting the Iv
	if (iv != 0)
	{
		Iv = (uint8_t*)iv;
	}

	for (i = 0; i < length; i += KEYLEN)
	{
		BlockCopy(output, input);
		state = (state_t*)output;
		InvCipher();
		XorWithIv(output);
		Iv = input;
		input += KEYLEN;
		output += KEYLEN;
	}

	if (remainders)
	{
		BlockCopy(output, input);
		memset(output + remainders, 0, KEYLEN - remainders); /* add 0-padding */
		state = (state_t*)output;
		InvCipher();
	}
}


#endif // #if defined(CBC) && CBC


int hexCharToValue(const char ch) {
	int result = 0;
	//获取16进制的高字节位数据
	if (ch >= '0' && ch <= '9') {
		result = (int)(ch - '0');
	}
	else if (ch >= 'a' && ch <= 'z') {
		result = (int)(ch - 'a') + 10;
	}
	else if (ch >= 'A' && ch <= 'Z') {
		result = (int)(ch - 'A') + 10;
	}
	else {
		result = -1;
	}
	return result;
}



int hexToStr(char *hex, char *ch)
{
	int high, low;
	int tmp = 0;
	if (hex == NULL || ch == NULL) {
		return -1;
	}

	if (strlen(hex) % 2 == 1) {
		return -2;
	}

	while (*hex) {
		high = hexCharToValue(*hex);
		if (high < 0) {
			*ch = '\0';
			return -3;
		}
		hex++; //指针移动到下一个字符上
		low = hexCharToValue(*hex);
		if (low < 0) {
			*ch = '\0';
			return -3;
		}
		tmp = (high << 4) + low;
		*ch++ = (char)tmp;
		hex++;
	}
	*ch = '\0';
	return 0;
}


