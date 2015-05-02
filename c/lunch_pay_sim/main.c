// Frederick Lee
// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <assert.h>
#include "pNode.h"
#include "pNodeFunc.h"
#include "lunchSimFunc.h"

#define MAX_STR_LENGTH 256

void printHelp()
{
	printf("lunch_pay_sim [options]\n");
	printf("options\n");
	printf("\t-l, --lunches [number of lunches for this sim]\n");
	printf("\t-o, --output [name of file to output data in CSV format]\n");
	printf("\t-f, --offset [price to add to represent big buyer]\n");
	printf("\t-h, --help\n");

	return;
}

void printCmdHelp()
{
	printf("Following commands and operations are available:\n");
	printf("\tadd <participant> - Adds particpant of name 'participant' to luncher pool.\n");
	printf("\tshow - Shows current state of luncher pool.\n");
	printf("\trun - Run the simulation and exit (for now).\n");
	printf("\texit - Exits this simulation.\n");
	printf("\thelp - Print this help. Congratulations, you found it!\n");
}

// main function to process options and decide what to do
int main(int argc, char** argv)
{
	// initializations and declarations
	char input[MAX_STR_LENGTH];
	char* command = "";

	int opt;
	PNODE* parList = NULL;
	int optionIndex = 0;

	unsigned char numLunches = 5;
	char* outputFile = "";
	double offset = 0.00;

	// process options
	static struct option longOptions[] = {
		{"lunches",	required_argument,	0,	'l'	},
		{"output",	required_argument,	0,	'o'	},
		{"offset",	required_argument,	0,	'f'	},
		{"help",	no_argument,		0,	'h'	},
		{0,		0,			0,	0	}
	};

	while((opt = getopt_long(argc, argv, "l:o:f:h", longOptions, &optionIndex)) != -1)
	{
		switch(opt)
		{
			case 'l':
				if(optarg)
				{
					numLunches = atoi(optarg);
					assert(numLunches > 0);
				}
				#ifdef DEBUG
				printf("option l - %d\n", numLunches);
				#endif
				break;
			case 'o':
				if(optarg)
				{
					outputFile = optarg;
				}
				#ifdef DEBUG
				printf("option o - %s\n", outputFile);
				#endif
				break;
			case 'f':
				if(optarg)
				{
					offset = atof(optarg);
					assert(offset > 0);
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
		printf("> ");
		fgets(input, MAX_STR_LENGTH, stdin); // TODO: check return code for anything meaningful

		#ifdef DEBUG
		printf("input is %s\n", input);
		#endif

		// parse with strtok
		command = strtok(input, " \n");

		#ifdef DEBUG
		printf("command is %s\n", command);
		#endif

		if(!command) // TODO: judge usefulness of this given above TODO.
		{
			command = "";
		}

		if(strcmp(command, "add") == 0) // add a participant
		{
			char* commandArg = strtok(NULL, " \n");
			if(!commandArg)
			{
				printf("Need argument: Participant name\n");
				continue;
			}

			if(strtok(NULL, " \n"))
			{
				printf("Too many arguments. Require no spaces in participant ID.\n");
				continue;
			}

			printf("Adding %s\n", commandArg);
			parList = addParticipant(parList, commandArg, offset);
		}
		else if(strcmp(command, "show") == 0) // check status through printing
		{
			parList = sortList(parList);
			printList(parList);
		}
		else if(strcmp(command, "run") == 0) // run simulation
		{
			// TODO: specify file to write in command. > run foo will output foo_prices.csv, foo_points.csv, foo_payer.csv
			// TODO: run no longer breaks. resets instead. run, reinitialize for subsequent run.
			runSimulation(parList, numLunches, outputFile);
			break;
		}
		else if(strcmp(command, "exit") == 0)
		{
			freeAll(parList);
			break;
		}
		else if(strcmp(command, "help") == 0)
		{
			printCmdHelp();
		}
		else // all other options. throw error.
		{
			printf("Unknown option. Try again.\n");
			printf("Enter help to get more info of available options.\n");
		}
	}
	return 0; // exit
}
