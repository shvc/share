#include <stdio.h>
#include <stdlib.h>

struct RandomListNode {
	int label;
	struct RandomListNode *next;
	struct RandomListNode *random;
};

void initList(struct RandomListNode **head, size_t len)
{
	int i = 0;
	struct RandomListNode *pcurrent = NULL;
	struct RandomListNode *pnode = NULL;

	pcurrent = malloc(sizeof(struct RandomListNode));
	pcurrent->label = 0;
	pcurrent->next = NULL;
	pcurrent->random = NULL;

	*head = pcurrent;

	for(i=1 ; i<len; i++) {
		pnode = malloc(sizeof(struct RandomListNode));
		pnode->label = i;
		pnode->next = NULL;
		pnode->random = pnode;
		
		pcurrent->next = pnode;
		pcurrent = pnode;
	}

}

void printList(struct RandomListNode *head)
{
	while ( head ) {
		printf("%p:%d ", head, head->label);
		if ( head->random ) {
			printf(", %p:%d ", head->random->label, head->random->label);
		}
		puts("");
		head = head->next;
	}
	puts("");
}

struct RandomListNode* copyRandomList(struct RandomListNode *head)
{
	struct RandomListNode* newNode = NULL;
	struct RandomListNode* pnext = NULL;
	struct RandomListNode* current = head;
	
	while( current ) {
		newNode = malloc(sizeof(struct RandomListNode));
		newNode->label = current->label;
		newNode->random = NULL;
		newNode->next = current->next;
		current->next = newNode;
		current = newNode->next;
	}

	current = head;
	while( current ) {
		pnext = current->next;
		if( current->random) {
			pnext->random = current->random->next;
		}
		else {
			pnext->random = NULL;
		}
		current = pnext->next;
	}

	current = head;
	newNode = head->next;

	while( current ) {
		pnext = current->next;
		current->next = pnext->next;
		current = pnext->next;
		if(current) {
			pnext->next=current->next;
		}
	}
		
	return newNode;

}


int main(int argc, char** argv)
{

	struct RandomListNode* head = NULL;
	struct RandomListNode* head2 = NULL;

	initList(&head, 10);
	puts("=========== head ===========");
	printList(head);

	head2 = copyRandomList(head);
	puts("=========== head ===========");
	printList(head);

	puts("=========== head2 ===========");
	printList(head2);

	return 0;
}

