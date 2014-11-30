// Frederick Lee
// lunch_pay_sim.c

#include <stdio.h>
#include <string.h>
#include "pNode.h"
#include "pNodeFunc.h"

int main(int argc, char** argv)
{
	unsigned int num_choice;

	while(1)
	{
		printf("Enter\n");
		printf("1 to add participant\n");
		printf("2 to end\n");
		scanf("%d", &num_choice);

		if(num_choice == 1)
		{
			printf("Add next participant here\n");
		}
		else if(num_choice == 2)
		{
			printf("Exiting\n");
			break;
		}
		else
		{
			printf("Unknown option. Try again.\n");
		}
	}
	return 0; // exit
}
