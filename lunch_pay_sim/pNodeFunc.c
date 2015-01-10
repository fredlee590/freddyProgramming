// pNodeFunc.c
// Define functions to be used with pNodes
// Frederick Lee

#include <stdlib.h>
#include <stdio.h> // maybe remove this after testing
#include <string.h>
#include "pNode.h"

void initParticipant(PNODE* parNodePtr, char* parName);
PNODE* addParticipant(PNODE* head, char* parName);
unsigned char get_length(PNODE* head);
PNODE* join_lists(PNODE* head1, PNODE* head2);
void printList(PNODE* head);
PNODE** transfer_node(unsigned char index, PNODE* from, PNODE* to);
void free_all(PNODE* head);

void initParticipant(PNODE* parNodePtr, char* parName)
{
	strcpy(parNodePtr->name, parName);
	parNodePtr->num_lunches = 0;
	parNodePtr->points = 0;
	parNodePtr->bought = 0.0;
	parNodePtr->paid = 0.0;
	parNodePtr->next = NULL;
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
		printf("    head: %s\n", head->name);
		printf("    head ptr: %p\n", head);
		PNODE* current = head;
		while(current->next != NULL)
		{
			printf("    passing %s\n", current->name);
			printf("    passing %p\n", current);
			current = current->next;
		}

		printf("    tail: %s\n", current->name);
		printf("    tail ptr: %p\n", current);
		PNODE *newPNODE = malloc(sizeof(PNODE));
		initParticipant(newPNODE, parName); // todo: move this out to another function for list
		current->next = newPNODE;
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
			current = current->next;
		}
		return count;
	}
}

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
			printf("\treturn: %.2f%%\n", (current->paid / current->bought) * 100.0);
			current = current->next;
		}
	}
}

PNODE** transfer_node(unsigned char index, PNODE* from, PNODE* to)
{
	PNODE** results = malloc(sizeof(PNODE*));
	#ifdef DEBUG
	printf("\t\tindex = %d\n", index);
	printf("\t\tfrom = %p\n", from);
	printf("\t\tto = %p\n", to);
	#endif

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

	#ifdef DEBUG
	printf("\t\ttarget name = %s\n", target->name);
	#endif

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

	#ifdef DEBUG
	printf("min_points = %d\n", min_points);
	#endif

	return result;
}

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
