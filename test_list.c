#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node * next;
};

void list_output(struct node* head)
{
	struct node* p = head;
	if( head ) {
		do {
			printf("%2i ", p->data);
			p = p->next;
		}while(p && p!=head);
		puts("");
	}
}
	
struct node* list_init()
{
	struct node *head = NULL;
	head = malloc(sizeof(struct node));
	if(head) {
		head->data = 0;
		head->next = NULL;
	}

	return head;
}

struct node* circular_list_init()
{
	struct node *head = NULL;
	head = malloc(sizeof(struct node));
	if(head) {
		head->data = 0;
		head->next = head;
	}

	return head;
}

struct node* list_add(struct node* head, int data)
{
	struct node* p = malloc(sizeof(struct node));
	if(p && head) {
		p->data = data;
		p->next = head->next;
		head->next = p;
	}
	
	return head;
}

struct node* is_circular(struct node* head)
{
	struct node* pret = NULL;
	struct node* p1 = head;
	struct node* p2 = head;

	if( head == NULL ) {
		return pret;
	}

	do {
		p1 = p1->next;
		p2 = p2->next;
		if(p2) {
			p2 = p2->next;
		}
		if( p2 && p1 == p2) {
			pret = p1;
			break;
		}
	} while (p1 && p2);

	return pret;
}

struct node* list_reverse(struct node* pnode)
{
	struct node* p = NULL;
	struct node* q = NULL;

	while(pnode) {
		p = pnode->next;
		pnode->next = q;
		q = pnode;
		pnode = p;
	}
	if(is_circular(q) == q) q=q->next;

	return q;
}

struct node* list_delete_node(struct node** head, struct node* pnode)
{
#if 0
	struct node* prev = *head;
	struct node* walk = *head;
	
	while( walk && walk != pnode) {
		prev = walk;
		walk = walk->next;
	}

	if(walk == *head && walk == pnode) {
		*head = walk->next;
		free(walk);
	}
	else if(walk == pnode) {
		prev->next = walk->next;
		free(walk);
	}
#else
	struct node **walk = head;

#endif

	return *head;
}

void list_free(struct node* head)
{
#if 0
	struct node *p = head;
	struct node *q = head;
	if( NULL == head ) {
		return;
	}

	do {
		q = p;
		p = p->next;
		free(q);
	} while (p && p != head);
#else
	while(head = list_delete_node(&head, head));
#endif

}

int main(int argc, char** argv)
{
	struct node* list_head;
	struct node* circular_list_head;

	list_head = list_init();
	list_output(list_head);
	list_head = list_reverse(list_head);
	list_output(list_head);

	list_add(list_head, 1);
	list_add(list_head, 2);
	list_add(list_head, 3);
	list_output(list_head);
	printf("is_circular: %i\n", is_circular(list_head));
	list_head = list_reverse(list_head);
	list_output(list_head);

	list_free(list_head);

	puts("------------------------------------");

	circular_list_head = circular_list_init();
	list_add(circular_list_head, 1);
	list_add(circular_list_head, 2);
	list_add(circular_list_head, 3);
	printf("is_circular: %i\n", is_circular(circular_list_head));
	list_output(circular_list_head);
	circular_list_head = list_reverse(circular_list_head);
	printf("is_circular: %i\n", is_circular(circular_list_head));
	list_output(circular_list_head);

	list_free(circular_list_head);

	return 0;
}

