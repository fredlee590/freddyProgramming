// pNode.h
// Define struct
// Frederick Lee

typedef struct pNode
{
	char name[256];
	unsigned char num_lunches;
	char points;
	double spent;
	struct pNode* next;
} PNODE;
