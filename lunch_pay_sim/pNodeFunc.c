// pNodeFunc.c
// Define functions to be used with pNodes
// Frederick Lee

#include <stdlib.h>
#include "pNode.h"

void initParticipant(PNODE* parNodePtr, char* parName)
{
	(*parNodePtr).name = parName;
	(*parNodePtr).num_lunches = 0;
	(*parNodePtr).points = 0;
	(*parNodePtr).spent = 0.0;
	(*parNodePtr).next = NULL;
}
