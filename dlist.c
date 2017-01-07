#include <stdio.h>
#include <stdlib.h>


struct list {
	int data;
	struct list *prev;
	struct list *next;
};


struct list* list_init(int n)
{
	int i;
	size_t size = 0;
	struct list *pn = NULL;
	struct list *p = NULL;


	size = sizeof(struct list);
	if(n <= 0) {
		return NULL;
	} else {
		p = malloc(size);
		p->data = 0;
		p->next = NULL;
		p->prev = NULL;
	}
	pn = p;

	for(i=1; i<n; i++) {
		p->next = malloc(size);
		p->next->prev = p;
		p = p->next;
		p->data = i;
	}
	p->next = NULL;

	return pn;
}


void list_print(struct list* pn)
{
	struct list *p = NULL;
	printf("output:\n");
	while(pn) {
		printf("%2d ", pn->data);
		p = pn;
		pn = pn->next;
	}
	printf("\nreverse output:\n");
	while(p) {
		printf("%2d ", p->data);
		p = p->prev;
	}
	printf("\n");
}


struct list* list_reverse(struct list* pn)
{
	struct list *q = NULL;
	struct list *p = NULL;

	while(pn) {
		p = pn->next;
		pn->next = q;
		pn->prev = p;
		q = pn;
		pn = p;
	}
	return q;
}

int main(int argc, char** argv)
{
	int ret;
	int len;
	struct list *head = NULL;

	printf("input length:");
	scanf("%d", &len);

	head = list_init(len);
	list_print(head);

	head = list_reverse(head);
	list_print(head);
	return ret;
}

