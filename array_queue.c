#include <stdio.h>
#include <stdlib.h>

struct queue {
	int front;
	int rear;
	int *array;
	size_t capacity;
	size_t size;
};

void init_queue(struct queue *q, size_t capacity) 
{
	q->capacity = capacity-1;
	q->size = 0;
	q->front = 0;
	q->rear = 0;
	q->array = malloc(sizeof(int) * capacity);
}

struct queue* create_queue(size_t capacity)
{
	struct queue *pqueue = malloc(sizeof(struct queue));
	init_queue(pqueue, capacity);
	
	return pqueue;
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
		q->array[q->rear] = x;
		q->rear = (q->rear+1)%(q->capacity);
	}
}

int dequeue(struct queue *q)
{
	int ret = 0;
	if( q->rear ==  q->front ) {
		puts("queue is empty");
	}
	else {
		ret = q->array[q->front];
		q->front = (q->front+1)%(q->capacity);
	}
	return ret;
}

int front(struct queue *q)
{
	int ret = 0;
	if(q->front == q->rear) {
		puts("queue is empty");
	}
	else {
		ret = q->array[q->front];
	}
	return ret;
}

int rear(struct queue *q)
{
	int ret = 0;
	if(q->front == q->rear) {
		puts("queue is empty");
	}
	else {
		ret = q->array[q->front];
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
	struct queue queue;
	init_queue(&queue, 10);
	
	enqueue(&queue, 1);
	enqueue(&queue, 2);
	enqueue(&queue, 3);
	enqueue(&queue, 4);
	enqueue(&queue, 5);
	enqueue(&queue, 6);
	printf("size: %d\n", size(&queue));
	printf("dequeue : %d\n", dequeue(&queue));
	printf("size: %d\n", size(&queue));
	printf("dequeue : %d\n", dequeue(&queue));
	printf("size: %d\n", size(&queue));
	printf("dequeue : %d\n", dequeue(&queue));
	printf("size: %d\n", size(&queue));
	printf("dequeue : %d\n", dequeue(&queue));
	printf("size: %d\n", size(&queue));
	printf("dequeue : %d\n", dequeue(&queue));
	printf("size: %d\n", size(&queue));
	enqueue(&queue, 70);
	enqueue(&queue, 80);
	printf("dequeue : %d\n", dequeue(&queue));
	printf("dequeue : %d\n", dequeue(&queue));
	printf("dequeue : %d\n", dequeue(&queue));
	printf("dequeue : %d\n", dequeue(&queue));

	return ret;
}

