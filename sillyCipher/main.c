// Frederick Lee
// main.c

#include <stdio.h>
#include <getopt.h>
#include "sillyCipherFunc.h"

void printHelp()
{
	printf("\n");
	printf("SillyCipher is a fun project to quickly encrypt strings\n");
	printf("\n");
	printf("It was originally conceived for simple, single words like passwords\n");
	printf("Usage:\n");
	printf("\tHahahahaha You didn't think it would be that easy, did you!?\n");
}

int main(int argc, char** argv)
{
	int opt;
	int option_index = 0;

	int curarg = 1;
	char* keyword = NULL;
	char direction = ENCRYPT;
	static struct option long_options[] = {
		{"decrypt",	no_argument,		0,	'd'	},
		{"keyword",	required_argument,	0,	'k'	},
		{"help",	no_argument,		0,	'h'	},
		{0,		0,			0,	0	}
	};

	// process options
	while((opt = getopt_long(argc, argv, "k:dh", long_options, &option_index)) != -1)
	{
		switch(opt)
		{
			case 'k':
				// assign keyword
				keyword = optarg;
				curarg++; // too many args?
				break;
			case 'h':
				// help
				printHelp();
				return 0;
			case 'd':
				// decrypt instead of default encrypt
				direction = DECRYPT;
			default:
				break;
		}
		curarg++; // too many args?
	}

	if(!keyword)
	{
		printf("Haha you suck!\n");

		return 0;
	}

	char* toXcrypt = argv[curarg++];

	if(curarg < argc)
	{
		printf("LOL nope!\n");
		return 2;
	}

	// print out encrypted string
	printf("%s\n", sillyXcrypt(keyword, toXcrypt, direction));

	return 0;
}
