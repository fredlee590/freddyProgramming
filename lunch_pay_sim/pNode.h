// pNode.h
// Define struct
// Frederick Lee

typedef struct pNode
{
	char* name;
	unsigned char num_lunches;
	char points;
	double spent;
	struct pNode* next;
} PNODE;
