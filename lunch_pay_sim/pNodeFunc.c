// pNodeFunc.c
// Define functions to be used with pNodes
// Frederick Lee

#include <stdlib.h>
#include <stdio.h> // maybe remove this after testing
#include <string.h>
#include <assert.h>
#include "pNode.h"

void initParticipant(PNODE* parNodePtr, char* parName);
PNODE* addParticipant(PNODE* head, char* parName, double offset);
unsigned char get_length(PNODE* head);
PNODE* join_lists(PNODE* head1, PNODE* head2);
void printList(PNODE* head);
PNODE** transfer_node(unsigned char index, PNODE* from, PNODE* to);
PNODE* sort_list(PNODE* head);
void free_all(PNODE* head);

// Initialize participant node. Set pNode to essentially a zero state with name.
// Input: Participant node, Participant name with which to initialize
// Output: none
void initParticipant(PNODE* parNodePtr, char* parName)
{
	assert(parNodePtr);

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
	if(!head)
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
	if(!head1)
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
// Input: pNode pointer indicating list to print
// Output: none
void printList(PNODE* head)
{
	if(!head)
	{
		printf("Participant list is null. Nothing to print\n");
	}
	else
	{
		PNODE* current = head;
		while(current)
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
	assert(get_length(from) >= index);

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
	if(!to)
	{
		to = target;
	}
	else
	{
		PNODE* cur = to;
		while(cur->next)
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

	while(cur)
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
	while(cur)
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

// Sort List alphabetically by participant name
// Input: pNode pointer indicating list of participants
// Output: pNode pointer indicating sorted list of participants
PNODE* sort_list(PNODE* head)
{
	// algorithm: pull head node and sort one by one. return sorted head
	PNODE* cur_head = head;
	PNODE* sorted_head = NULL;
	PNODE* sort_cand = NULL;

	// for entire list
	while(cur_head)
	{
		sort_cand = cur_head;
		#ifdef DEBUG
		printf("sort_cand = %s\n", sort_cand->name);
		#endif
		cur_head = cur_head->next;

		if(!sorted_head)
		{
			// essentially create sorted head
			sorted_head = sort_cand;
			sorted_head->next = NULL;
		}
		else if(strcmp(sort_cand->name, sorted_head->name) < 0)
		{
			// candidate should go before current head
			sort_cand->next = sorted_head;
			sorted_head = sort_cand;
		}
		else
		{
			// search to the right to find right place for sort_cand
			PNODE* cur_sorted = sorted_head;
			char* cand_name = sort_cand->name;

			while(cur_sorted->next && strcmp(cur_sorted->next->name, cand_name) < 0)
			{
				cur_sorted = cur_sorted->next;
			}

			sort_cand->next = cur_sorted->next;
			cur_sorted->next = sort_cand;
		}
	}

	return sorted_head;
}

// Free all nodes at the end of the sim
// Input: pNode pointer indicating list of participants
// Output: none
void free_all(PNODE* head)
{
	assert(head);

	if(!head->next)
	{
		free(head);
	}
	else
	{
		free_all(head->next);
	}
}
