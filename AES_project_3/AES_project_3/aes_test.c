
#include "aes.h"

/*AES_128�������ݣ��ַ�����
*input:�������� -- unsigned char*
*key:��Կ��16�ֽڣ�-- unsigned char*
*output:������� -- unsigned char*
*

void all_AES128_ECB_encrypt(const uint8_t* input, const uint8_t* key, uint8_t* output);

*/

/*AES_128�������ݣ��ַ�����
*input:�������� -- unsigned char*
*key:��Կ��16�ֽڣ�-- unsigned char*
*output:������� -- unsigned char*

void all_AES128_ECB_decrypt(const uint8_t* input, const uint8_t* key, uint8_t *output)

*/

int main(int argc, char *argv[])
{
	int i = 0;
	unsigned char *plain = "123456789123456789";
	unsigned char *key = "abcdefghijklmnop";

	unsigned char cipher[1024] = { 0 };
	unsigned char temp[1024] = { 0 };

	all_AES128_ECB_encrypt(plain, key, cipher);//���ܣ�plainΪ���ģ�keyΪ��Կ��cipherΪ���ܺ�����

	for (i = 0;i < ((strlen(plain)/16)+1)*16;i++) {

		printf("%x", cipher[i]);
	}
	printf("\n");


	all_AES128_ECB_decrypt(cipher, key, temp);//���ܣ�cipherΪ���ģ�keyΪ��Կ��tempΪ���ܺ�����
	
	for (i = 0;i < strlen(plain);i++) {
		
		printf("%c", temp[i]);
	 }
	 
	getchar();

	return(0);
}
