
#include "3des.h"

/************************************************************************
* 3DES-ECB加密方式
* 8字节密钥，加密内容8位补齐，补齐方式为：PKCS7。
* 
************************************************************************/

/************************************************************************
* DES-ECB加密方式
* 1字节密钥，加密内容8位补齐，补齐方式为：PKCS7。
* 
************************************************************************/


int main(int argc, char *argv[])
{
	unsigned char *key = "abcdefjh";

	unsigned char *data = "12345678";  /* 原始明文 */

	unsigned char out[1024] = { 0 };

	unsigned char tmp[1024] = { 0 };

	int datalen = strlen(data);

	D3DES_Encrypt(data,key,out, datalen); //加密

	int len = (datalen / 8 + 1) * 8;

	int i = 0;
	for (i = 0; i < len; i++) {
		printf("%x", *(out + i));
	}
	printf("\n");

	D3DES_Decrypt(out, key,tmp, datalen); //解密

	for (i = 0; i < datalen; i++) {
		printf("%c", *(tmp + i));
	}

	getchar();

	return 0;
}




