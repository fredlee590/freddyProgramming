// Frederick Lee
// main.c

#include <stdio.h>
#include <string.h>
#include "pNode.h"
#include "pNodeFunc.h"
#include "lunchSimFunc.h"

int main(int argc, char** argv)
{
	unsigned int num_choice;
	PNODE* parList = NULL;

	/*
	todo: use getopt to include options. at least the following:
	1) number of lunches
	2) output to csv file with <input file name>.csv
		lunch_num,name,points,bought,paid,ratio,payer_y_n
	3) offset for initial head
	*/

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
			#ifdef DEBUG
			run_simulation(parList, 5); // 5 lunches for test / development
			#endif
			run_simulation(parList, 200); // 200 lunches for production
			break;
		}
		else
		{
			printf("Unknown option. Try again.\n");
		}
	}
	return 0; // exit
}
