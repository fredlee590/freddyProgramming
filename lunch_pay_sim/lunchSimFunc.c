// lunchSimFunc.c
// Define simulation support functions here
// Frederick Lee

#include <stdlib.h> // random
#include <time.h> // time to use for seed random
#include <stdio.h> // printing
#include <string.h> // string check
#include "pNode.h" // primary data structure
#include "pNodeFunc.h" // pNode functions

#define BASE_PRICE 10.0
#define PRICE_RANGE 500

// print help
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

// actually run simulation
// input: pNode function indicating participant list, number of lunches
// output: none
void run_simulation(PNODE* head, unsigned char num_lunches, char* output_file_name)
{
	if(!head || !head->next)
	{
		printf("Not enough lunch participants!\nUseless simulation!\n");
		return;
	}

	unsigned char i;
	PNODE** linked_lists = malloc(sizeof(PNODE*));
	linked_lists[0] = head;

	if(num_lunches < 2)
	{
		printf("Need at least 2 lunches for a meaningful simulation\n");
		return;
	}

	unsigned char max_num_lunchers = get_length(head);
	FILE* output_file = NULL;

	if(strlen(output_file_name) > 0)
	{
		output_file = fopen(output_file_name, "w+");
	}

	printf("===== SIMULATION BEGINS =====\n");
	printf("Number of lunches = %d\n", num_lunches);
	printf("Maximum number of lunchers = %d\n", max_num_lunchers);
	printf("output file = %s\n", output_file_name);
	printf("=============================\n");
	printf("Run simulation. All logic goes here\n");

	srand(time(NULL)); // reseed random numbers based on time of run

	printf("\n");

	// do this for all lunches
	for(i = 1; i <= num_lunches; i++)
	{
		printf("----- Lunch %d -----\n", i);
		double lunchSum = 0.0;
		unsigned char j;
		unsigned char num_lunchers = (rand() % (max_num_lunchers - 1)) + 2; // at least two, max max_num_lunchers

		PNODE* lunchers = NULL;
		linked_lists[1] = lunchers;

		// build up luncher list for this lunch
		for(j = 0; j < num_lunchers; j++)
		{
			// pull one luncher from main list to current lunch's lunchers
			unsigned char cur_size = max_num_lunchers - j;
			unsigned char k = rand() % cur_size;
			linked_lists = transfer_node(k, head, lunchers);

			head = linked_lists[0];
			lunchers = linked_lists[1];
		}

		// determine payer
		PNODE* payer = findPayer(lunchers);
		printf("payer = %s\n", payer->name);

		// for each luncher for this lunch
		PNODE* cur_luncher = lunchers;
		while(cur_luncher != NULL)
		{
			double lunchPrice = ((rand() % PRICE_RANGE) / 100.0) + BASE_PRICE + cur_luncher->offset;

			cur_luncher->bought += lunchPrice;
			lunchSum += lunchPrice;
			cur_luncher->num_lunches++;

			if(output_file)
			{
				fprintf(output_file, "%d,%s,%.2f,%d,%s\n", i, cur_luncher->name, lunchPrice, cur_luncher->points, payer->name);
			}

			cur_luncher = cur_luncher->next;
		}

		// calculate payer stuff
		lunchers = updatePoints(lunchers, payer->name, num_lunchers);
		payer->paid += lunchSum;

		printList(lunchers);

		head = join_lists(head, lunchers);
	}

	if(output_file)
	{
		fclose(output_file);
	}

	printf("\n===== FINAL TALLY =====\n\n");
	printList(head);
	free_all(head);
}
