#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

struct node {
	int data;
	struct node* next;
};

void push(struct node **top, int data)
{
	struct node *pnode = malloc(sizeof(struct node));
	
	pnode->data = data;
	pnode->next = *top;

	*top = pnode;
}

int pop(struct node **top)
{
	int retval = INT_MIN;
	struct node *pnode = *top;

	if(pnode) {
		retval = pnode->data;
		*top = pnode->next;
		free(pnode);
	}
	else {
		puts("empty stack");
	}

	return retval;
}

int peek(struct node *top)
{
	if(top) {
		return top->data;
	}
	else {
		return INT_MIN;
	}
}

int is_empty(struct node *top)
{

	return top==NULL?1:0;
}

void empty(struct node **top)
{
	struct node *pnode = *top;
	struct node *walk = pnode;

	while(pnode) {
		walk = pnode->next;
		free(pnode);
		pnode = walk;
	}
	*top = NULL;
}

void test()
{
	struct node* stack = NULL;

	push(&stack, 1);
	push(&stack, 2);
	assert(2 == pop(&stack));
	assert(1 == pop(&stack));
	assert(INT_MIN == pop(&stack));
	push(&stack, 3);
	assert(3 == pop(&stack));
	assert(INT_MIN == pop(&stack));
}

int main(int argc, char** argv)
{
	struct node* stack = NULL;

	test();

	push(&stack, 1);
	push(&stack, 2);
	push(&stack, 3);
	push(&stack, 4);

	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	empty(&stack);

	return 0;
}
