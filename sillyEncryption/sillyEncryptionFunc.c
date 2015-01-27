/*
 * sillyEncryptionFunc.c
 *
 * Contains the encryption and support functions for encryption
 */

#include <openssl/md5.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

char* sillyEncrypt(char* keyword, char* toEncrypt)
{
	#ifdef DEBUG
	int i;
	#endif

	MD5_CTX c;
	unsigned char out[MD5_DIGEST_LENGTH];

	// create default (empty) string
	char* result = "";

	// compute md5sum of keyword
	unsigned long keyword_len = strlen(keyword);

	MD5_Init(&c);
	MD5_Update(&c, keyword, keyword_len);

	MD5_Final(out, &c);

	#ifdef DEBUG
	for(i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
		printf("%02x", out[i]);
	}

	printf("\n");
	#endif

	// walk down each part of the md5sum (bitmask)
	// get corresponding part of string to encrypt

	// compute offset from md5sum part
	// add or subtract md5sum part to or from string to encrypt
	// append to result string

	// return result

	return result;
}
