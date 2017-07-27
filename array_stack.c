#include <stdio.h>

#define STACK_SIZE 64

int stack[STACK_SIZE];
int top = -1;

int push(int x)
{
	int ret = 0;
	if(top < STACK_SIZE-1) {
		stack[++top] = x;
	}
	else {
		puts("stack is full");
		ret = 1;
	}

	return ret;
}

int pop()
{
	int ret = 0;
	if( top>=0 ) {
		ret = stack[top--];
	}
	else {
		puts("stack is empty");
	}
	return ret;
}

int peek()
{
	int ret = 0;
	if(top >= 0) {
		ret = stack[top];
	}
	else {
		puts("stack is empty");
	}
	return ret;
}

int main(int argc, char** argv)
{
	int ret = 0;
	
	push(1);
	push(2);
	push(3);
	push(4);
	push(5);
	push(6);
	push(7);
	push(8);
	printf("peek: %d\n", peek());
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());
	push(70);
	push(80);
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());
	printf("pop : %d\n", pop());

	return ret;
}

