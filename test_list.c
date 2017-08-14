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

void list_print(struct node *head)
{
	struct node *ptr = head;
	printf("[ ");

	if(head != NULL) {
		while(ptr->next != ptr) {     
			printf("%d ",ptr->data);
			ptr = ptr->next;
		}
	}

	printf(" ]\n");
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

struct node* list_add_node(struct node* head, int data)
{
	struct node* p;
	if(NULL == head) {
		return head;
	}
	p = malloc(sizeof(struct node));
	if(p) {
		p->data = data;
		p->next = head->next;
		head->next = p;
	}

	return head;
}

struct node* list_add_nodes(struct node* head, size_t cnt)
{
	struct node* p = NULL;

	if(NULL == head) {
		return head;
	}
	for(; cnt>0; cnt--) {
		p = malloc(sizeof(struct node));
		if(p) {
			p->data = cnt;
			p->next = head->next;
			head->next = p;
		}
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

struct node* circular(struct node *head)
{
	struct node *ret = NULL;
	struct node *p1 = head;
	struct node *p2 = head;
	size_t len_p1 = 0;
	size_t len_p2 = 0;

	if(p1 == NULL) {
		return ret;
	}

	do {
		len_p1++;
		p1 = p1->next;
		len_p2 = 1;
		for(p2=head; p2 != p1; p2=p2->next) {
			len_p2++;
		}
		if(p2==p1 && len_p2!=len_p1) {
			ret = p2;
			break;
		}
	} while(p1);

	return ret;
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
	struct node **walk = head;

	while(*walk && *walk != pnode) {
		walk = &((*walk)->next);
	}
	if(*walk) {
		*walk = pnode->next;
		free(pnode);
	}

	return *head;
}

struct node* list_delete_nodes(struct node* head, int val)
{
	struct node **walk = &head;
	struct node *tmp = NULL;

	while(*walk) {
		if((*walk)->data == val) {
			tmp = *walk;
			*walk = (*walk)->next;
			free(tmp);
		}
		else {
			walk = &((*walk)->next);
		}
	}
	return head;
}

void list_free(struct node* head)
{
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

}

int main(int argc, char** argv)
{
	struct node* list_head;
	struct node* circular_list_head;

	list_head = list_init();
	list_output(list_head);
	list_head = list_reverse(list_head);
	list_output(list_head);

	list_add_node(list_head, 1);
	list_add_node(list_head, 2);
	list_add_nodes(list_head, 3);
	list_add_node(list_head, 2);
	list_add_node(list_head, 2);
	list_output(list_head);
	printf("is_circular: %i\n", is_circular(list_head));
	list_head = list_reverse(list_head);
	list_output(list_head);
	list_head = list_delete_nodes(list_head, 2);
	list_output(list_head);

	list_free(list_head);

	puts("------------------------------------");

	circular_list_head = circular_list_init();
	list_add_node(circular_list_head, 1);
	list_add_node(circular_list_head, 2);
	list_add_nodes(circular_list_head, 3);
	list_add_node(circular_list_head, 2);
	list_add_node(circular_list_head, 2);
	printf("is_circular: %i\n", is_circular(circular_list_head));
	printf("   circular: %i\n", circular(circular_list_head));
	list_output(circular_list_head);
	circular_list_head = list_reverse(circular_list_head);
	printf("is_circular: %i\n", is_circular(circular_list_head));
	printf("   circular: %i\n", circular(circular_list_head));
	list_output(circular_list_head);
	circular_list_head = list_delete_nodes(circular_list_head, 2);
	list_output(circular_list_head);

	list_free(circular_list_head);

	return 0;
}

