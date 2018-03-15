
#include "aes.h"

/*AES_128加密数据（字符串）
*input:输入数据 -- unsigned char*
*key:密钥（16字节）-- unsigned char*
*output:输出数据 -- unsigned char*
*

void all_AES128_ECB_encrypt(const uint8_t* input, const uint8_t* key, uint8_t* output);

*/

/*AES_128解密数据（字符串）
*input:输入数据 -- unsigned char*
*key:密钥（16字节）-- unsigned char*
*output:输出数据 -- unsigned char*

void all_AES128_ECB_decrypt(const uint8_t* input, const uint8_t* key, uint8_t *output)

*/

int main(int argc, char *argv[])
{
	int i = 0;
	unsigned char *plain = "123456789123456789";
	unsigned char *key = "abcdefghijklmnop";

	unsigned char cipher[1024] = { 0 };
	unsigned char temp[1024] = { 0 };

	all_AES128_ECB_encrypt(plain, key, cipher);//加密，plain为明文，key为密钥，cipher为加密后数据

	for (i = 0;i < ((strlen(plain)/16)+1)*16;i++) {

		printf("%x", cipher[i]);
	}
	printf("\n");


	all_AES128_ECB_decrypt(cipher, key, temp);//解密，cipher为密文，key为密钥，temp为解密后数据
	
	for (i = 0;i < strlen(plain);i++) {
		
		printf("%c", temp[i]);
	 }
	 
	getchar();

	return(0);
}
