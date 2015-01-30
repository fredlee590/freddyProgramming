/*
 * sillyXcryptionFunc.c
 *
 * Contains the encryption and support functions for encryption
 */

#include <openssl/md5.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR '~'
#define APOS 39
#define MINCHAR ' '
#define RANGE (MAXCHAR - MINCHAR + 1)

char* sillyXcrypt(char* keyword, char* toXcrypt, char initialDir)
{
	int i;
	MD5_CTX c;
	unsigned char out[MD5_DIGEST_LENGTH];

	// set up defaults
	char sign = initialDir;

	char* result = malloc(sizeof(char)*strlen(toXcrypt));

	// compute md5sum of keyword
	unsigned long keyword_len = strlen(keyword);
	unsigned int toXcrypt_len = strlen(toXcrypt);

	strcpy(result, toXcrypt);

	MD5_Init(&c);
	MD5_Update(&c, keyword, keyword_len);

	MD5_Final(out, &c);

	// walk down each part of the md5sum
	for(i = 0; i < toXcrypt_len; i++)
	{
		// compute offset from md5sum part
		unsigned char offset = out[i % MD5_DIGEST_LENGTH] & 0xF;

		// initialize to relative target
		#ifdef DEBUG
		printf("newChar = %c + (%d * %d)\n", result[i], sign, offset);
		#endif

		unsigned char newChar = result[i] + (sign * offset);

		if(newChar < MINCHAR)
		{
			#ifdef DEBUG
			printf("newChar %c (%d) is less than '!'\n", newChar, newChar);
			#endif
			newChar += RANGE;
			#ifdef DEBUG
			printf("new newChar %c (%d)\n", newChar, newChar);
			#endif
		}
		else if(newChar > MAXCHAR)
		{
			#ifdef DEBUG
			printf("newChar %c (%d) is greater than '~'\n", newChar, newChar);
			#endif
			newChar -= RANGE;
			#ifdef DEBUG
			printf("new newChar %c (%d)\n", newChar, newChar);
			#endif
		}

		#ifdef DEBUG
		printf("%d %c %c %d\n", i, result[i], newChar, newChar);
		#endif

		// add or subtract md5sum part to or from string to encrypt
		result[i] = newChar;

		// special case: Need to reserve apostrophes for use on the command line
		if(newChar == APOS)
		{
			i--;
			continue;
		}

		sign *= -1;
	}

	#ifdef DEBUG
	printf("result = %s\n", result);
	#endif

	return result;
}