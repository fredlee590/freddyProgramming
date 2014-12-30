// lunchSimFunc.c
// Define simulation support functions here
// Frederick Lee

//#include <stdlib.h> // random
//#include <time.h> // time to use for seed random
#include <stdio.h> // printing
#include "pNode.h" // primary data structure
#include "pNodeFunc.h" // pNode functions

void run_simulation(PNODE* head, unsigned char N)
{
	unsigned char i;
	if(N < 2)
	{
		printf("Need at least 2 lunches for a meaningful simulation\n");
		return;
	}

	printf("\tFind max number of lunchers\n");
	unsigned char max_num_lunchers = get_length(head);

	printf("===== SIMULATION BEGINS =====\n");
	printf("Number of lunches = %d\n", N);
	printf("Maximum number of lunchers = %d\n", max_num_lunchers);
	printf("=============================\n");
	printf("Run simulation. All logic goes here\n");

	printf("\n");
	printf("For each of the %d lunches...\n", N);
	for(i = 1; i <= N; i++)
	{
		//unsigned char num_lunchers;

		printf("----- Lunch %d -----\n", i);

		printf("\tGenerate random number A of lunchers for this lunch\n");

		printf("\tGenerate A random numbers to select A lunchers to add to luncher list\n");
		printf("\tFor each of the A lunchers selected for this lunch\n");
		printf("\t\tGenerate random modifier X to add to base lunch price\n");
		printf("\t\tAdd 10 + X to lunch sum S\n");
		printf("\t\tTODO: Add 10 + X to personal tally under bought\n");
		printf("\t\tIncrement personal tally under num_lunches\n");
		printf("\tDetermine luncher with fewest points to designate as payer\n");
		printf("\tUpdate points : Subtract 1 point from all non-payer players : Add A - 1 points to payer\n");
		printf("\tAdd lunch sum S to payer's paid field\n");
	}

	printf("Print out final numbers for all possible lunchers\n");
	printList(head);
}
