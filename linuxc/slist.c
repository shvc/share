#include <stdio.h>
#include <stdlib.h>

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
	puts("==========");

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
	struct node *walk = *pnode;
	struct node *current = NULL;

	while( walk ) {
		current = walk->next;
		free(walk);
		walk = current;
	}
	*pnode = NULL;

	return 0;
}

struct node* reverse(struct node *head)
{
	struct node *prev = NULL;
	struct node *next, *current = head;

	while(current) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}

	return prev;
}

/*
   * return the node where the cycle begins.
    * If there is no cycle, return null
     */
struct node* has_cycle(struct node* head)
{
        struct node* pret = NULL;
        struct node* p_fast = head;
        struct node* p_slow = head;

        while(p_slow && p_fast && p_fast->next) {
                p_slow = p_slow->next;
                p_fast = p_fast->next->next;
                if( p_slow == p_fast ) {
                        for(p_fast=head; p_slow != p_fast; p_fast=p_fast->next, p_slow=p_slow->next);
                        pret = p_slow;
                        break;
                }
        }

        return pret;
}

/*
   * return the node where the cycle begins.
    * If there is no cycle, return null
     */
struct node* detect_cycle(struct node *head)
{
        struct node *ret = NULL;
        struct node *p1 = head;
        struct node *p2 = head;
        size_t len_p1 = 0;
        size_t len_p2 = 0;

        while(p1) {
                len_p1++;
                p1 = p1->next;
                len_p2 = 0;
                for(p2=head; p2 != p1; p2=p2->next) {
                        len_p2++;
                }
                if(len_p2 != len_p1) {
                        ret = p2;
                        break;
                }
        };

        return ret;
}


struct node* delete(struct node **head, struct node *node)
{

	return *head;
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
	/*
	list_delete(&pnode, pnode);
	list_delete(&pnode, pnode->next);
	list_delete(&pnode, (struct node*)1234);
	*/
	pnode = list_reverse(pnode);
	list_print(pnode);

	pnode = reverse(pnode);
	list_print(pnode);


	list_free(&pnode->next);
	list_print(pnode);
	/*
	list_free(&pnode);
	list_free(&pnode);
	*/
}

