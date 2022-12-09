#include <stdio.h>
#include <limits.h>
#include <assert.h>

#define STACK_SIZE 64

int stack[STACK_SIZE];
int top = -1;

void push(int x)
{
	if(top < STACK_SIZE-1) {
		stack[++top] = x;
	}
	else {
		puts("stack is full");
	}
}

int pop()
{
	int ret = INT_MIN;
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
	int ret = INT_MIN;
	if(top >= 0) {
		ret = stack[top];
	}
	else {
		puts("stack is empty");
	}
	return ret;
}

int size()
{
	return top+1;
}

void test()
{
        push(1);
        push(2);
        assert(2 == pop());
        assert(1 == pop());
        assert(INT_MIN == pop());
        push(3);
        assert(3 == pop());
        assert(INT_MIN == pop());
}


int main(int argc, char** argv)
{
	int ret = 0;
	
	test();

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

