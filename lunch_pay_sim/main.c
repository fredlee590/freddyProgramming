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
			run_simulation(parList, 5); // 5 lunches for test / development
			break;
		}
		else
		{
			printf("Unknown option. Try again.\n");
		}
	}
	return 0; // exit
}
