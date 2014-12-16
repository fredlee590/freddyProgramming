// lunchSimFunc.c
// Define simulation support functions here
// Frederick Lee

#include <stdio.h> // printing
#include "pNode.h" // primary data structure

void run_simulation(PNODE* head, unsigned char N)
{
	unsigned char i;
	double lunch_sum;
	for(i = 0; i < N; i++)
	{
		lunch_sum = 0.0;
		printf("Lunch %d\n", i);
		// select lunchers for this lunch
		// for each of these lunchers
			// add food cost to sum of lunch
			// increment lunches participated in

		// select payer based on current points
		// update points
		// update spent of payer
		// add lunchers back to end of the line
	}

}
