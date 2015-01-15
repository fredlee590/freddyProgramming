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

void printHelp()
{
	printf("lunch_pay_sim [options]\n");
	printf("options\n");
	printf("\t-l, --lunches [number of lunches for this sim]\n");
	printf("\t-o, --output [name of file to output data in CSV format]\n");
	printf("\t-b, --bigbuyer [price to add to represent big buyer]\n");
	printf("\t-h, --help\n");

	return;
}

void run_simulation(PNODE* head, unsigned char N)
{
	if(head == NULL) // replace with assert (get some practice there)
	{
		printf("No lunch participants!\nUseless simulation!\n");
		return;
	}

	unsigned char i;
	PNODE** linked_lists = malloc(sizeof(PNODE*));
	linked_lists[0] = head;

	if(N < 2)
	{
		printf("Need at least 2 lunches for a meaningful simulation\n");
		return;
	}

	#ifdef DEBUG
	printf("\tFind max number of lunchers\n");
	#endif
	unsigned char max_num_lunchers = get_length(head);

	printf("===== SIMULATION BEGINS =====\n");
	printf("Number of lunches = %d\n", N);
	printf("Maximum number of lunchers = %d\n", max_num_lunchers);
	printf("=============================\n");
	printf("Run simulation. All logic goes here\n");

	srand(time(NULL)); // reseed random numbers based on time of run

	printf("\n");
	#ifdef DEBUG
	printf("For each of the %d lunches...\n", N);
	#endif
	for(i = 1; i <= N; i++)
	{
		double lunchSum = 0.0;
		unsigned char j;
		printf("----- Lunch %d -----\n", i);

		#ifdef DEBUG
		printf("\tGenerate random number A of lunchers for this lunch\n");
		#endif
		unsigned char num_lunchers = (rand() % (max_num_lunchers - 1)) + 2; // at least two, max max_num_lunchers
		#ifdef DEBUG
		printf("\tNum lunchers for this lunch = %d\n", num_lunchers);
		#endif

		PNODE* lunchers = NULL;
		linked_lists[1] = lunchers;

		#ifdef DEBUG
		printf("\tGenerate A random numbers to select A lunchers to add to luncher list\n");
		#endif
		for(j = 0; j < num_lunchers; j++)
		{
			// pull one luncher from main list to current lunch's lunchers
			#ifdef DEBUG
			printf("\tLuncher #%d\n", j);
			#endif
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

		#ifdef DEBUG
		printf("\tFor each of the A lunchers selected for this lunch\n");
		#endif
		PNODE* cur_luncher = lunchers;
		while(cur_luncher != NULL)
		{
			#ifdef DEBUG
			printf("\t\tGenerate random modifier X to add to base lunch price\n");
			#endif
			double lunchPrice = ((rand() % PRICE_RANGE) / 100.0) + BASE_PRICE;

			#ifdef DEBUG
			printf("\t\tTODO: Add 10 + X to personal tally under bought\n");
			#endif
			cur_luncher->bought += lunchPrice;

			#ifdef DEBUG
			printf("\t\tAdd 10 + X to lunch sum S\n");
			#endif
			lunchSum += lunchPrice;

			#ifdef DEBUG
			printf("\t\tIncrement personal tally under num_lunches\n");
			#endif
			cur_luncher->num_lunches++;

			cur_luncher = cur_luncher->next;
		}

		#ifdef DEBUG
		printf("\tDetermine luncher with fewest points to designate as payer\n");
		#endif
		PNODE* payer = findPayer(lunchers);

		printf("payer = %s\n", payer->name);

		#ifdef DEBUG
		printf("\tUpdate points : Subtract 1 point from all non-payer players : Add A - 1 points to payer\n");
		#endif
		lunchers = updatePoints(lunchers, payer->name, num_lunchers);

		#ifdef DEBUG
		printf("\tAdd lunch sum S to payer's paid field\n");
		#endif
		payer->paid += lunchSum;

		printList(lunchers);

		#ifdef DEBUG
		printf("\tRecombine lunchers to master list to prepare for next lunch\n");
		#endif
		head = join_lists(head, lunchers);
	}

	printf("\n===== FINAL TALLY =====\n\n");
	printList(head);
	free_all(head);
}
