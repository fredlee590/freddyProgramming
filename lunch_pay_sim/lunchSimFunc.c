// lunchSimFunc.c
// Define simulation support functions here
// Frederick Lee

#include <stdlib.h> // random
#include <time.h> // time to use for seed random
#include <stdio.h> // printing
#include "pNode.h" // primary data structure
#include "pNodeFunc.h" // pNode functions

#define BASE_PRICE 10.0
#define PRICE_RANGE 500

void run_simulation(PNODE* head, unsigned char N)
{
	unsigned char i;
	PNODE** linked_lists = malloc(sizeof(PNODE*));
	linked_lists[0] = head;

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

	srand(time(NULL)); // reseed random numbers based on time of run

	printf("\n");
	printf("For each of the %d lunches...\n", N);
	for(i = 1; i <= N; i++)
	{
		double lunchSum = 0.0;
		unsigned char j;
		printf("----- Lunch %d -----\n", i);

		printf("\tGenerate random number A of lunchers for this lunch\n");
		unsigned char num_lunchers = (rand() % (max_num_lunchers - 1)) + 2; // at least two, max max_num_lunchers
		printf("\tNum lunchers for this lunch = %d\n", num_lunchers);

		PNODE* lunchers = NULL;
		linked_lists[1] = lunchers;

		printf("\tGenerate A random numbers to select A lunchers to add to luncher list\n");
		for(j = 0; j < num_lunchers; j++)
		{
			// pull one luncher from main list to current lunch's lunchers
			printf("\tLuncher #%d\n", j);
			unsigned char cur_size = max_num_lunchers - j;
			unsigned char k = rand() % cur_size;
			linked_lists = transfer_node(k, head, lunchers);

			head = linked_lists[0];
			lunchers = linked_lists[1];
		}

		#ifdef DEBUG
		printf("HEAD\n");
		printList(head);
		printf("LUNCHERS\n");
		printList(lunchers);
		#endif

		printf("\tFor each of the A lunchers selected for this lunch\n");
		PNODE* cur_luncher = lunchers;
		while(cur_luncher != NULL)
		{
			printf("\t\tGenerate random modifier X to add to base lunch price\n");
			double lunchPrice = ((rand() % PRICE_RANGE) / 100.0) + BASE_PRICE;

			printf("\t\tTODO: Add 10 + X to personal tally under bought\n");
			cur_luncher->bought += lunchPrice;

			printf("\t\tAdd 10 + X to lunch sum S\n");
			lunchSum += lunchPrice;

			printf("\t\tIncrement personal tally under num_lunches\n");
			cur_luncher->num_lunches++;

			cur_luncher = cur_luncher->next;
		}

		printf("\tDetermine luncher with fewest points to designate as payer\n");
		PNODE* payer = findPayer(lunchers);

		#ifdef DEBUG
		printf("payer = %s\n", payer->name);
		#endif

		printf("\tUpdate points : Subtract 1 point from all non-payer players : Add A - 1 points to payer\n");
		lunchers = updatePoints(lunchers, payer->name, num_lunchers);

		printf("\tAdd lunch sum S to payer's paid field\n");
		payer->paid += lunchSum;

		printf("\tRecombine lunchers to master list to prepare for next lunch\n");
		head = join_lists(head, lunchers);
	}

	printf("Print out final numbers for all possible lunchers\n");
	printList(head);
}
