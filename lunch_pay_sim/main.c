// Frederick Lee
// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "pNode.h"
#include "pNodeFunc.h"
#include "lunchSimFunc.h"

int main(int argc, char** argv)
{
	unsigned int num_choice;
	int opt;
	PNODE* parList = NULL;
	int option_index = 0;

	unsigned char num_lunches = 5;
	char output_file[256] = ""; // todo: make this more robust
	double offset = 0.00;

	/*
	todo: use getopt to include options. at least the following:
	1) number of lunches
	2) output to csv file with <input file name>.csv
		lunch_num,name,points,bought,paid,ratio,payer_y_n
	3) offset for initial head
	*/

	static struct option long_options[] = {
		{"lunches",	required_argument,	0,	'l'	},
		{"output",	required_argument,	0,	'o'	},
		{"bigbuyer",	required_argument,	0,	'b'	},
		{"help",	no_argument,		0,	'h'	},
		{0,		0,			0,	0	}
	};

	while((opt = getopt_long(argc, argv, "l:o:b:h", long_options, &option_index)) != -1)
	{
		switch(opt)
		{
			case 'l':
				if(optarg)
				{
					num_lunches = atoi(optarg);
				}
				printf("option l - %d\n", num_lunches);
				break;
			case 'o':
				if(optarg)
				{
					strcpy(output_file, optarg);
				}
				printf("option o - %s\n", output_file);
				break;
			case 'b':
				if(optarg)
				{
					offset = atof(optarg);
				}
				printf("option b - %.2f\n", offset);
				break;
			case 'h':
				printHelp();
				break;
			case '?':
				printf("option ?\n");
				break;
			default:
				printf("unknown option - %d\n", opt);
				break;
		}
	}

	while(1)
	{
		printf("Enter\n");
		printf("    1 to add participant\n");
		printf("    2 to print participants\n");
		printf("    3 to run simulation\n\n");
		scanf("%d", &num_choice);

		if(num_choice == 1)
		{
			char newName[256] = "";
			printf("Add next participant here\n");
			scanf("%s", newName);
			parList = addParticipant(parList, newName);
		}
		else if(num_choice == 2)
		{
			printf("Exiting\n");
			printList(parList);
		}
		else if(num_choice == 3)
		{
			run_simulation(parList, num_lunches); // 5 lunches for test / development
			break;
		}
		else
		{
			printf("Unknown option. Try again.\n");
		}
	}
	return 0; // exit
}
