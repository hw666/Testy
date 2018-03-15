
#include "3des.h"

/************************************************************************
* 3DES-ECB���ܷ�ʽ
* 8�ֽ���Կ����������8λ���룬���뷽ʽΪ��PKCS7��
* 
************************************************************************/

/************************************************************************
* DES-ECB���ܷ�ʽ
* 1�ֽ���Կ����������8λ���룬���뷽ʽΪ��PKCS7��
* 
************************************************************************/


int main(int argc, char *argv[])
{
	unsigned char *key = "abcdefjh";

	unsigned char *data = "12345678";  /* ԭʼ���� */

	unsigned char out[1024] = { 0 };

	unsigned char tmp[1024] = { 0 };

	int datalen = strlen(data);

	D3DES_Encrypt(data,key,out, datalen); //����

	int len = (datalen / 8 + 1) * 8;

	int i = 0;
	for (i = 0; i < len; i++) {
		printf("%x", *(out + i));
	}
	printf("\n");

	D3DES_Decrypt(out, key,tmp, datalen); //����

	for (i = 0; i < datalen; i++) {
		printf("%c", *(tmp + i));
	}

	getchar();

	return 0;
}




