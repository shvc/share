#include <stdio.h>

#define QUEUE_SIZE 6

int queue[QUEUE_SIZE];
int front = 0;
int rear = 0;

int isfull()
{
	int ret = 0;
	if( (rear+1)%QUEUE_SIZE == front) {
		ret = 1;
	}

	return ret;
}

void enqueue(int x)
{
	if( isfull() ) {
		puts("queue is full");
	}
	else {
		queue[rear] = x;
		rear = (rear+1)%QUEUE_SIZE;
	}
}

int dequeue()
{
	int ret = 0;
	if( rear ==  front ) {
		puts("queue is empty");
	}
	else {
		ret = queue[front];
		front = (front+1)%QUEUE_SIZE;
	}
	return ret;
}

int peek()
{
	int ret = 0;
	if(front == rear) {
		puts("queue is empty");
	}
	else {
		ret = queue[front];
	}
	return ret;
}


int size()
{
	return (rear+QUEUE_SIZE-front)%QUEUE_SIZE;
}

int main(int argc, char** argv)
{
	int ret = 0;
	
	enqueue(1);
	enqueue(2);
	enqueue(3);
	enqueue(4);
	enqueue(5);
	enqueue(6);
	printf("peek: %d\n", peek());
	printf("size: %d\n", size());
	printf("dequeue : %d\n", dequeue());
	printf("size: %d\n", size());
	printf("dequeue : %d\n", dequeue());
	printf("size: %d\n", size());
	printf("dequeue : %d\n", dequeue());
	printf("size: %d\n", size());
	printf("dequeue : %d\n", dequeue());
	printf("size: %d\n", size());
	printf("dequeue : %d\n", dequeue());
	printf("size: %d\n", size());
	enqueue(70);
	enqueue(80);
	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());
	printf("dequeue : %d\n", dequeue());

	return ret;
}

