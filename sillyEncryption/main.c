// Frederick Lee
// main.c

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include "sillyEncryptionFunc.h"

void printHelp()
{
	printf("\n");
	printf("SillyEncryption is a fun project to quickly encrypt strings\n");
	printf("\n");
	printf("It was originally conceived for simple, single words like passwords\n");
	printf("Usage:\n");
	printf("\tsillyEncryption [options] -k [keyword] [string(s) to encrypt]\n");
	printf("Options:\n");
	printf("\t-h, --help: Display this help message\n");
	printf("\t-k, --key [keyword]: Need a keyword with which to encrypt the argument(s) (required)\n");
	printf("\n");
}

int main(int argc, char** argv)
{
	int opt;
	int option_index = 0;

	char keyword[N] = "";
	static struct option long_options[] = {
		{"help",	no_argument,		0,	'h'	},
		{"keyword",	required_argument,	0,	'k'	},
		{0,		0,			0,	0	}
	};

	// process options
	while((opt = getopt_long(argc, argv, "k:h", long_options, &option_index)) != -1)
	{
		switch(opt)
		{
			case 'k':
				strcpy(keyword, optarg);
				break;
			case 'h':
				printHelp();
				return 0;
			default:
				break;
		}
	}

	if(strcmp("", keyword) == 0)
	{
		printf("Must have a keyword with which to encrypt arguments.\n");

		return 0;
	}
	else
	{
		printf("Proceeding with encryption. Keyword is %s\n", keyword);
	}

	// algorithm for encryption

	// print out encrypted string
	printf("%s\n", sillyEncrypt(keyword, "blahblahblah"));

	return 0; // exit
}
