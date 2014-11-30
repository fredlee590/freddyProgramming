// Frederick Lee
// lunch_pay_sim.c

#include <stdio.h>

int main(int argc, char** argv)
{
	// initializations
	// todo: contain info in struct and pass struct around?
	unsigned char num_participants = 6;
	unsigned char num_lunches = 30;
	unsigned char i;

	// declarations
	// todo: List node?
	unsigned char points[num_participants];
	unsigned char money_paid[num_participants];

	// initialize arrays (todo: FUNCTION)
	// common key = user ID
	for(i = 0; i < num_participants; i++)
	{
		points[i] = 0;
		money_paid[i] = 0;
	}

	// cycle through lunches and fill up array (todo: FUNCTION)
	for(i = 0; i < num_lunches; i++)
	{
		printf("%d\n", i);
	}

	// print final information per participant, including (todo: FUNCTION)
	// 1) Dollar amount spent
	// 2) Number of lunches paid 
	for(i = 0; i < num_participants; i++)
	{
		printf("person %d paid %d and has %d points\n", i, money_paid[i], points[i]);
	}

	return 0; // exit
}
