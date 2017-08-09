#include <stdio.h>
#include <stdlib.h>

struct queue {
	int front;
	int rear;
	int *array;
	size_t capacity;
	size_t size;
};

struct queue* create_queue(size_t capacity)
{
	struct queue *pqueue = malloc(sizeof(struct queue));
	init_queue(pqueue, capacity);
	
	return pqueue;
}

void init_queue(struct queue *q, size_t capacity) 
{
	q->capacity = capacity-1;
	q->size = 0;
	q->front = 0;
	q->rear = 0;
	q->array = malloc(sizeof(int) * capacity);
}

void destroy_queue(struct queue* queue)
{
	if(queue) {
		free(queue->array);
	}
	free(queue);
}

int isfull(struct queue *q)
{
	int ret = 0;
	if( ((q->rear)+1)%(q->capacity) == q->front) {
		ret = 1;
	}

	return ret;
}

void enqueue(struct queue* q, int x)
{
	if( isfull(q) ) {
		puts("queue is full");
	}
	else {
		q->array[rear] = x;
		rear = (rear+1)%(q->capacity);
	}
}

int dequeue(struct queue *q)
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

int front(struct queue *q)
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

int rear(struct queue *q)
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


int size(struct queue *q)
{
	return q->size;
}

void test()
{

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

