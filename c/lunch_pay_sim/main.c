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

// main function to process options and decide what to do
int main(int argc, char** argv)
{
	// initializations and declarations
	char input[MAX_STR_LENGTH];
	char* command = "";

	int opt;
	PNODE* parList = NULL;
	int option_index = 0;

	unsigned char num_lunches = 5;
	char* output_file = "";
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
					assert(num_lunches > 0);
				}
				#ifdef DEBUG
				printf("option l - %d\n", num_lunches);
				#endif
				break;
			case 'o':
				if(optarg)
				{
					output_file = optarg;
				}
				#ifdef DEBUG
				printf("option o - %s\n", output_file);
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

	// TODO: Transfer this to a command line type structure. Commands like
	//       add <participant name> 1
	//       del <participant name> ? 2
	//       show 1
	//       run 1
	//       quit 2
	//       help 3

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
			char* command_arg = strtok(NULL, " \n");
			if(!command_arg)
			{
				printf("Need argument: Participant name\n");
				continue;
			}

			if(strtok(NULL, " \n"))
			{
				printf("Too many arguments. Require no spaces in participant ID.\n");
				continue;
			}

			printf("Adding %s\n", command_arg);
			parList = addParticipant(parList, command_arg, offset);
		}
		else if(strcmp(command, "show") == 0) // check status through printing
		{
			parList = sort_list(parList);
			printList(parList);
		}
		else if(strcmp(command, "run") == 0) // run simulation
		{
			run_simulation(parList, num_lunches, output_file);
			break;
		}
		else if(strcmp(command, "exit") == 0)
		{
			free_all(parList);
			return 0;
		}
		else // all other options. throw error.
		{
			printf("Unknown option. Try again.\n");
		}
	}
	return 0; // exit
}
