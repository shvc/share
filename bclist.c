/*
 * bidirectional circuled linked list
 */
#include <stdio.h>
#include <stdlib.h>

struct bclist {
	struct bclist *next;
	struct bclist *prev;
	int data;
};

struct bclist* bclist_init(int data)
{
	struct bclist *p = malloc(sizeof(struct bclist));
	if(p) {
		p->next = p;
		p->prev = p;
		p->data = data;
	}
	return p;
}

struct bclist* bclist_add(struct bclist* h, int data)
{
	struct bclist *p = h;

	if(NULL == h) {
		return h;
	}

	do {
		if(p->data == data) {
			return h;
		}
		p = p->next;
	}while(p != h);

	p = malloc(sizeof(struct bclist));
	if(NULL == p) {
		return h;
	}
	p->next = h;
	p->prev = h->prev;
	h->prev = p;
	p->prev->next = p;

	p->data = data;

	return h;
}

struct bclist* bclist_delete(struct bclist* h, int data)
{
	struct bclist *p = h;
	struct bclist *q = NULL;
	
	do {
		if(p->data == data) {
			q = p;
			p = p->prev;
			q->next->prev = q->prev;
			q->prev->next = q->next;
			free(q);	
		}
		p = p->next;
	} while(p != h);

	return h;
}

struct bclist* bclist_release(struct bclist* h)
{
	struct bclist* p = h;
	do {
		p = p->next;
	} while(p != h);

	return h;
}

void bclist_print(struct bclist* h)
{
	struct bclist* p = h;

	do {
		printf("%d ", p->data);
		p = p->next;
	}while(p != h);

	printf("\n");
}

int main(int argc, char** argv)
{
	const int ret = 0;
	struct bclist* h = NULL;

	h = bclist_init(0);
	bclist_add(h, 1);
	bclist_add(h, 2);
	bclist_add(h, 3);
	bclist_add(h, 2);
	bclist_print(h);

	bclist_delete(h, 2);
	bclist_add(h, 5);
	bclist_print(h);
	bclist_release(h);
	bclist_print(h);

	return ret;
}

