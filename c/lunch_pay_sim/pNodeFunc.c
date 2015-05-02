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
unsigned char getLength(PNODE* head);
PNODE* joinLists(PNODE* head1, PNODE* head2);
void printList(PNODE* head);
PNODE** transferNode(unsigned char index, PNODE* from, PNODE* to);
PNODE* sortList(PNODE* head);
void freeAll(PNODE* head);

// Initialize participant node. Set pNode to essentially a zero state with name.
// Input: Participant node, Participant name with which to initialize
// Output: none
void initParticipant(PNODE* parNodePtr, char* parName)
{
	assert(parNodePtr);

	strcpy(parNodePtr->name, parName);
	parNodePtr->numLunches = 0;
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
		while(current->next)
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
unsigned char getLength(PNODE* head)
{
	if(!head)
	{
		return 0;
	}
	else
	{
		unsigned char count = 0;
		// traverse list and count
		PNODE* current = head;
		while(current)
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
PNODE* joinLists(PNODE* head1, PNODE* head2)
{
	if(!head1)
	{
		return head2;
	}
	else
	{
		// get to end of first list
		PNODE* current = head1;

		while(current->next)
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
			printf("\tnumLunches: %d\n", current->numLunches);
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
PNODE** transferNode(unsigned char index, PNODE* from, PNODE* to)
{
	assert(getLength(from) >= index);

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
	char minPoints = 127;
	char* result = "";

	while(cur)
	{
		char curPoints = cur->points;
		if(curPoints < minPoints)
		{
			minPoints = curPoints;
			result = cur->name;
		}
		cur = cur->next;
	}

	return result;
}

// Update points based on specified payer and number of people on the lunch
// Input: pNode pointer indicating list, payer name, number of lunchers for points
// Output: pNode pointer indicating list
PNODE* updatePoints(PNODE* head, char* payerName, unsigned char numLunchers)
{
	PNODE* cur = head;
	while(cur)
	{
		if(strcmp(cur->name, payerName) == 0)
		{
			cur->points += numLunchers - 1;
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
PNODE* sortList(PNODE* head)
{
	// algorithm: pull head node and sort one by one. return sorted head
	PNODE* curHead = head;
	PNODE* sortedHead = NULL;
	PNODE* sortCand = NULL;

	// for entire list
	while(curHead)
	{
		sortCand = curHead;
		#ifdef DEBUG
		printf("sortCand = %s\n", sortCand->name);
		#endif
		curHead = curHead->next;

		if(!sortedHead)
		{
			// essentially create sorted head
			sortedHead = sortCand;
			sortedHead->next = NULL;
		}
		else if(strcmp(sortCand->name, sortedHead->name) < 0)
		{
			// candidate should go before current head
			sortCand->next = sortedHead;
			sortedHead = sortCand;
		}
		else
		{
			// search to the right to find right place for sortCand
			PNODE* curSorted = sortedHead;
			char* candName = sortCand->name;

			while(curSorted->next && strcmp(curSorted->next->name, candName) < 0)
			{
				curSorted = curSorted->next;
			}

			sortCand->next = curSorted->next;
			curSorted->next = sortCand;
		}
	}

	return sortedHead;
}

// Free all nodes at the end of the sim
// Input: pNode pointer indicating list of participants
// Output: none
void freeAll(PNODE* head)
{
	if(head)
	{
		freeAll(head->next);
		free(head);
	}
	else
	{
		return;
	}
}
