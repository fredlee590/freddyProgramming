// Frederick Lee
// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "pNode.h"
#include "pNodeFunc.h"
#include "lunchSimFunc.h"

// main function to process options and decide what to do
int main(int argc, char** argv)
{
	// initializations and declarations
	unsigned int num_choice;
	int opt;
	PNODE* parList = NULL;
	int option_index = 0;

	unsigned char num_lunches = 5;
	char output_file[256] = ""; // todo: make this more robust
	double offset = 0.00;

	// process options
	static struct option long_options[] = {
		{"lunches",	required_argument,	0,	'l'	},
		{"output",	required_argument,	0,	'o'	},
		{"offset",	required_argument,	0,	'f'	},
		{"help",	no_argument,		0,	'h'	},
		{0,		0,			0,	0	}
	};

	while((opt = getopt_long(argc, argv, "l:o:f:h", long_options, &option_index)) != -1)
	{
		switch(opt)
		{
			case 'l':
				if(optarg)
				{
					num_lunches = atoi(optarg);
				}
				#ifdef DEBUG
				printf("option l - %d\n", num_lunches);
				#endif
				break;
			case 'o':
				if(optarg)
				{
					strcpy(output_file, optarg);
				}
				#ifdef DEBUG
				printf("option o - %s\n", output_file);
				#endif
				break;
			case 'f':
				if(optarg)
				{
					offset = atof(optarg);
				}
				#ifdef DEBUG
				printf("option b - %.2f\n", offset);
				#endif
				break;
			case 'h':
				printHelp();
				return 0;
			case '?':
				printf("option ?\n");
				return 1;
			default:
				printf("unknown option - %d\n", opt);
				break;
		}
	}

	// decide what to do
	while(1)
	{
		printf("Enter\n");
		printf("    1 to add participant\n");
		printf("    2 to print participants\n");
		printf("    3 to run simulation\n\n");
		scanf("%d", &num_choice);

		if(num_choice == 1) // add a participant
		{
			char newName[256] = "";
			printf("Add next participant here\n");
			scanf("%s", newName);
			parList = addParticipant(parList, newName, offset);
		}
		else if(num_choice == 2) // check status through printing
		{
			printList(parList);
		}
		else if(num_choice == 3) // run simulation
		{
			run_simulation(parList, num_lunches, output_file);
			break;
		}
		else // all other options. throw error.
		{
			printf("Unknown option. Try again.\n");
		}
	}
	return 0; // exit
}
