// pNodeFunc.c
// Define functions to be used with pNodes
// Frederick Lee

#include <stdlib.h>
#include <stdio.h> // maybe remove this after testing
#include <string.h>
#include "pNode.h"

void initParticipant(PNODE* parNodePtr, char* parName);
PNODE* addParticipant(PNODE* head, char* parName, double offset);
unsigned char get_length(PNODE* head);
PNODE* join_lists(PNODE* head1, PNODE* head2);
void printList(PNODE* head);
PNODE** transfer_node(unsigned char index, PNODE* from, PNODE* to);
void free_all(PNODE* head);

// Initialize participant node. Set pNode to essentially a zero state with name.
// Input: Participant node, Participant name with which to initialize
// Output: none
void initParticipant(PNODE* parNodePtr, char* parName)
{
	strcpy(parNodePtr->name, parName);
	parNodePtr->num_lunches = 0;
	parNodePtr->points = 0;
	parNodePtr->bought = 0.0;
	parNodePtr->paid = 0.0;
	parNodePtr->offset = 0.0;
	parNodePtr->next = NULL;
}

// Add new participant to participant list
// Input: Head pNode pointer to indicate list, participant name to initialize, participant price offset
// Output: Head pNode pointer to indicate list
PNODE* addParticipant(PNODE* head, char* parName, double offset)
{
	if ( head == NULL )
	{
		printf("    Empty list. Adding first participant\n");
		head = malloc(sizeof(PNODE));
		initParticipant(head, parName);
		head->offset = offset;
	}
	else
	{
		printf("    Adding participant %s\n", parName);

		// get to the end
		PNODE* current = head;
		while(current->next != NULL)
		{
			current = current->next;
		}

		PNODE *newPNODE = malloc(sizeof(PNODE));
		initParticipant(newPNODE, parName); // todo: move this out to another function for list
		current->next = newPNODE;
	}
	return head;
}

// Traverses given list and return tallied length. List must be less than 255 nodes
// todo: handle this by either exiting, or increasing maximum length
// Input: Head pNode pointer
// Output: number indicating how long the node is
unsigned char get_length(PNODE* head)
{
	if(head == NULL)
	{
		return 0;
	}
	else
	{
		unsigned char count = 0;
		// traverse list and count
		PNODE* current = head;
		while(current != NULL)
		{
			count++;
			current = current->next;
		}
		return count;
	}
}

// Combine two lists
// Input: pNode pointer indicating first pNode list, pNode pointer indicating second pNode list
// Output: pNode pointer of the two combined lists
PNODE* join_lists(PNODE* head1, PNODE* head2)
{
	if(head1 == NULL)
	{
		return head2;
	}
	else
	{
		// get to end of first list
		PNODE* current = head1;

		while(current->next != NULL)
		{
			current = current->next;
		}

		current->next = head2;

		return head1;
	}
}

// Print important information in list
// todo: print data in CSV format if --output option is set
// Input: pNode pointer indicating list to print
// Output: none
void printList(PNODE* head)
{
	if ( head == NULL )
	{
		printf("Participant list is null. Nothing to print\n");
	}
	else
	{
		PNODE* current = head;
		while(current != NULL)
		{
			printf("Participant: %s\n", current->name);
			#ifdef DEBUG
			printf("\tAddr: %p\n", current);
			#endif
			printf("\tnum_lunches: %d\n", current->num_lunches);
			printf("\tpoints: %d\n", current->points);
			printf("\tbought: %.2f\n", current->bought);
			printf("\tpaid: %.2f\n", current->paid);
			printf("\toffset: %.2f\n", current->offset);
			printf("\tROI: %.2f%%\n", (current->bought / current->paid) * 100.0);
			current = current->next;
		}
	}
}

// Move pNode from one list to another. Change references around.
// Input: Index indicating which node to move, pNode pointer indicating source list, pNode pointer indicating destination list
// Output: Array of pNode pointers indicating both pNode pointers
PNODE** transfer_node(unsigned char index, PNODE* from, PNODE* to)
{
	PNODE** results = malloc(sizeof(PNODE*));

	// ----- transfer actually occurs here -----
	PNODE* target;

	// if index == 0, index'th node is first and need to change from and to pointers.
	// if index > 0, need to hunt for index'th node.
	if(index == 0)
	{
		target = from;
		from = from->next;
	}
	else
	{
		unsigned char i;
		PNODE* prev = from;
		target = from->next;
		for(i = 1; i < index; i++)
		{
			prev = prev->next;
			target = target->next;
		}
		prev->next = target->next;
	}

	// update to list
	if(to == NULL)
	{
		to = target;
	}
	else
	{
		PNODE* cur = to;
		while(cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = target;
	}

	target->next = NULL;

	results[0] = from;
	results[1] = to;

	return results;
}

// Choose a payer from a given list
// Input: pNode pointer indicating list to search
// Output: Name of payer
char* findPayer(PNODE* head)
{
	PNODE* cur = head;
	char min_points = 127;
	char* result = "";

	while(cur != NULL)
	{
		char cur_points = cur->points;
		if(cur_points < min_points)
		{
			min_points = cur_points;
			result = cur->name;
		}
		cur = cur->next;
	}

	return result;
}

// Update points based on specified payer and number of people on the lunch
// Input: pNode pointer indicating list, payer name, number of lunchers for points
// Output: pNode pointer indicating list
PNODE* updatePoints(PNODE* head, char* payerName, unsigned char num_lunchers)
{
	PNODE* cur = head;
	while(cur != NULL)
	{
		if(strcmp(cur->name, payerName) == 0)
		{
			cur->points += num_lunchers - 1;
		}
		else
		{
			cur->points--;
		}
		cur = cur->next;
	}
	return head;
}

// Free all nodes at the end of the sim
// Input: pNode pointer indicating list of participants
// Output: none
void free_all(PNODE* head)
{
	if(head->next == NULL)
	{
		free(head);
	}
	else
	{
		free_all(head->next);
	}
}
