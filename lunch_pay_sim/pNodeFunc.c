// pNodeFunc.c
// Define functions to be used with pNodes
// Frederick Lee

#include <stdlib.h>
#include <stdio.h> // maybe remove this after testing
#include <string.h>
#include "pNode.h"

void initParticipant(PNODE* parNodePtr, char* parName)
{
	strcpy((*parNodePtr).name, parName);
	//(*parNodePtr).name = parName;
	(*parNodePtr).num_lunches = 0;
	(*parNodePtr).points = 0;
	(*parNodePtr).spent = 0.0;
	(*parNodePtr).next = NULL;
}

PNODE* addParticipant(PNODE* head, char* parName)
{
	if ( head == NULL )
	{
		printf("    Empty list. Adding first participant\n");
		head = malloc(sizeof(PNODE));
		initParticipant(head, parName);
	}
	else
	{
		printf("    Adding participant %s\n", parName);

		// get to the end
		printf("    head: %s\n", (*head).name);
		printf("    head ptr: %p\n", head);
		PNODE* current = head;
		while((*current).next != NULL)
		{
			printf("    passing %s\n", (*current).name);
			printf("    passing %p\n", current);
			current = (*current).next;
		}

		printf("    tail: %s\n", (*current).name);
		printf("    tail ptr: %p\n", current);
		PNODE *newPNODE = malloc(sizeof(PNODE));
		initParticipant(newPNODE, parName); // todo: move this out to another function for list
		(*current).next = newPNODE;
	}
	return head;
}

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
			current = (*current).next;
		}
		return count;
	}
}

PNODE* join_lists(PNODE* head1, PNODE* head2)
{
	// get to end of first list
	PNODE* current = head1;

	while((*current).next != NULL)
	{
		current = (*current).next;
	}

	(*current).next = head2;

	return head1;
}

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
			printf("Addr: %p\n", current);
			printf("    Participant: %s\n", (*current).name);
			printf("    num_lunches: %d\n", (*current).num_lunches);
			printf("    points: %d\n", (*current).points);
			printf("    spent: %.2f\n", (*current).spent);
			current = (*current).next;
		}
	}
}
