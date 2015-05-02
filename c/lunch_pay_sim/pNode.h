// pNode.h
// Define struct
// Frederick Lee

typedef struct pNode
{
	char name[256];
	unsigned char numLunches;
	char points;
	double bought;
	double paid;
	double offset;
	struct pNode* next;
} PNODE;
