#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* next;
};

struct stack {
	struct node *head;
};


int push(struct stack *stack, int data)
{
	int ret = 0;
	struct node *pnode = NULL;

	pnode = malloc(sizeof(struct node));
	
	pnode->data = data;
	pnode->next = stack->head;

	stack->head = pnode;

	return 0;
}

int pop(struct stack *stack)
{
	int ret = 0;
	struct node *pnode = stack->head;

	if(pnode) {
		ret = pnode->data;
		stack->head = pnode->next;
		free(pnode);
	}
	else {
		puts("empty stack");
	}

	return ret;
}

int main(int argc, char** argv)
{
	int x;

	struct stack stack;
	stack.head = NULL;

	push(&stack, 1);
	push(&stack, 2);
	push(&stack, 3);
	push(&stack, 4);

	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));

	return 0;
}
