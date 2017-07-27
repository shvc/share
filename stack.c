#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* next;
};

struct stack {
	struct node *top;
};


int push(struct stack *stack, int data)
{
	int ret = 0;
	struct node *pnode = NULL;

	pnode = malloc(sizeof(struct node));
	
	pnode->data = data;
	pnode->next = stack->top;

	stack->top = pnode;

	return 0;
}

int pop(struct stack *stack)
{
	int ret = 0;
	struct node *pnode = stack->top;

	if(pnode) {
		ret = pnode->data;
		stack->top = pnode->next;
		free(pnode);
	}
	else {
		puts("empty stack");
	}

	return ret;
}

int peek(struct stack *stack)
{
	if(stack && stack->top) {
		return stack->top->data;
	}
	else {
		return 0;
	}
}

int is_empty(struct stack *stack)
{

	return stack->top==NULL?1:0;
}

int main(int argc, char** argv)
{
	int x;

	struct stack stack;
	stack.top = NULL;

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
