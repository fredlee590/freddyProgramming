#ifndef PNODEFUNC_H
#define PNODEFUNC_H

void initParticipant(PNODE* parNodePtr, char* parName);
PNODE* addParticipant(PNODE* parNodePtr, char* parName, double offset);
PNODE* join_lists(PNODE* head1, PNODE* head2);
unsigned char get_length(PNODE* parNodePtr);
void printList(PNODE* parNodePtr);
PNODE** transfer_node(unsigned char index, PNODE* from, PNODE* to);
PNODE* findPayer(PNODE* head);
PNODE* updatePoints(PNODE* head, char* payerName, unsigned char num_lunchers);
PNODE* sort_list(PNODE* head);
void free_all(PNODE* head);

#endif
