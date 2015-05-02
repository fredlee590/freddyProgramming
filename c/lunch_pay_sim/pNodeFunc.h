#ifndef PNODEFUNC_H
#define PNODEFUNC_H

void initParticipant(PNODE* parNodePtr, char* parName);
PNODE* addParticipant(PNODE* parNodePtr, char* parName, double offset);
PNODE* joinLists(PNODE* head1, PNODE* head2);
unsigned char getLength(PNODE* parNodePtr);
void printList(PNODE* parNodePtr);
PNODE** transferNode(unsigned char index, PNODE* from, PNODE* to);
PNODE* findPayer(PNODE* head);
PNODE* updatePoints(PNODE* head, char* payerName, unsigned char numLunchers);
PNODE* sortList(PNODE* head);
void freeAll(PNODE* head);

#endif
