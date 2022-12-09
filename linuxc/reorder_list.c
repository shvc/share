#include <stdio.h>
#include <stdlib.h>

/*
 * Given a sigly linked list L:(L0, L1, L2, ... Ln-1, Ln)
 * Write a function to reorder it so that it becomes(L0, Ln, L1, Ln-1, L2, Ln-2 ...)
 */

struct node {
	int data;
	struct node *next;
};

struct node* list_init(int length)
{
	int i = 0;
	struct node *p, *q;
	if(length <= 0) {
		return NULL;
	}else{
		p = malloc(sizeof(struct node));
		p->data = 0;
	}
	for(i=1, q=p; i<length; i++) {
		q->next = malloc(sizeof(struct node));
		q = q->next;
		q->data = i;
	}
	q->next = NULL;

	return p;
}

int list_print(struct node *pnode)
{
	int i;
	for(i=0; pnode; i++) {
		printf("node[%i]: %i\n", i, pnode->data);
		pnode = pnode->next;
	}

	return 0;
}

struct node* list_reverse(struct node *pnode)
{
	struct node *p, *q = NULL;
	while( pnode ) {
		p = pnode->next;
		pnode->next = q;
		q = pnode;
		pnode = p;
	}

	return q;
}

int list_free(struct node **pnode)
{
	struct node **walk = pnode;
	struct node *current = NULL;

	while( *walk ) {
		current = *walk;
		walk = &(*walk)->next;
		free(current);
	}
	*pnode = NULL;

	return 0;
}

struct node* list_delete(struct node **head, struct node *p)
{
#if 0 /* poor taste */
	struct node *prev = NULL;
	struct node *walk = *head;

	while( walk != p && walk ) {
		prev = walk;
		walk = walk->next;
	}

	if( walk == *head ) {
		*head = walk->next;
		free(walk);
	}
	else if( p == walk) {
		prev->next = walk->next;
		free(walk);
	}

#else /* Good teate */
	struct node **walk = head;

	while( *walk != p && *walk ) {
		walk = &((*walk)->next);
	}
	
	if(*walk) {
		*walk = p->next;
		free(p);
	}

#endif
	return *head;
}

int main(int argc, char* argv[])
{
	int len;
	struct node *pnode = NULL;

	printf("input number:");
	scanf("%i", &len);

	pnode = list_init(len);
	list_print(pnode);
	list_delete(&pnode, pnode);
	list_delete(&pnode, pnode->next);
	list_delete(&pnode, (struct node*)1234);
	list_print(pnode);

	list_print(list_reverse(pnode));


	list_free(&pnode->next->next);
	list_free(&pnode->next);
	list_free(&pnode);
}

