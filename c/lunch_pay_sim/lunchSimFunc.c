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

// actually run simulation
// input: pNode function indicating participant list, number of lunches
// output: none
void runSimulation(PNODE* head, unsigned char numLunches, char* outputFileName)
{
	if(!head || !head->next)
	{
		printf("Not enough lunch participants!\nUseless simulation!\n");
		return;
	}

	unsigned char i;
	PNODE** linkedLists = malloc(sizeof(PNODE*));
	linkedLists[0] = head;

	if(numLunches < 2) // assert with error message?
	{
		printf("Need at least 2 lunches for a meaningful simulation\n");
		return;
	}

	unsigned char maxNumLunchers = getLength(head);
	FILE* outputFile = NULL;

	if(strlen(outputFileName) > 0)
	{
		outputFile = fopen(outputFileName, "w+");
	}

	printf("===== SIMULATION BEGINS =====\n");
	printf("Number of lunches = %d\n", numLunches);
	printf("Maximum number of lunchers = %d\n", maxNumLunchers);
	printf("output file = %s\n", outputFileName);
	printf("=============================\n");
	printf("Run simulation. All logic goes here\n");

	srand(time(NULL)); // reseed random numbers based on time of run

	printf("\n");

	// do this for all lunches
	for(i = 1; i <= numLunches; i++)
	{
		printf("----- Lunch %d -----\n", i);
		double lunchSum = 0.0;
		unsigned char j;
		unsigned char numLunchers = (rand() % (maxNumLunchers - 1)) + 2; // at least two, max maxNumLunchers

		PNODE* lunchers = NULL;
		linkedLists[1] = lunchers;

		// build up luncher list for this lunch
		for(j = 0; j < numLunchers; j++)
		{
			// pull one luncher from main list to current lunch's lunchers
			unsigned char curSize = maxNumLunchers - j;
			unsigned char k = rand() % curSize;
			linkedLists = transferNode(k, head, lunchers);

			head = linkedLists[0];
			lunchers = linkedLists[1];
		}

		// determine payer
		PNODE* payer = findPayer(lunchers);
		printf("payer = %s\n", payer->name);

		// for each luncher for this lunch
		PNODE* curLuncher = lunchers;
		while(curLuncher)
		{
			double lunchPrice = ((rand() % PRICE_RANGE) / 100.0) + BASE_PRICE + curLuncher->offset;

			curLuncher->bought += lunchPrice;
			lunchSum += lunchPrice;
			curLuncher->numLunches++;

			curLuncher = curLuncher->next;
		}

		// calculate payer stuff
		lunchers = updatePoints(lunchers, payer->name, numLunchers);
		payer->paid += lunchSum;

		printList(lunchers);

		head = joinLists(head, lunchers);

		// TODO 1: sort here and print out based on that order
		// TODO 2: print out to file if applicable
		head = sortList(head);
		if(outputFile)
		{
			fprintf(outputFile, "%d", i);
			PNODE* writePtr = head;
			while(writePtr)
			{
				// TODO: raw price data goes here. Headings, etc also should be here
				fprintf(outputFile, ",%.2f", writePtr->bought);
				writePtr = writePtr->next;
			}
			fprintf(outputFile, "\n");
		}
	}

	if(outputFile)
	{
		fclose(outputFile);
	}

	printf("\n===== FINAL TALLY =====\n\n");
	printList(head);
	freeAll(head);
}
