#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
	int data;
	struct node* next;
};

struct queue {
	struct node *front;
	struct node *rear;
	size_t length;
};

void init(struct queue *queue)
{
	queue->front = NULL;
	queue->rear = NULL;
	queue->length = 0;
}

int enqueue(struct queue *queue, int data)
{

	struct node *pnode = malloc(sizeof(struct node));
	pnode->data = data;
	pnode->next = NULL;

	if(queue->rear == NULL) {
		queue->rear = pnode;
		queue->front = pnode;
	}
	else {
		queue->rear->next = pnode;
		queue->rear = pnode;
	}
	queue->length++;

	return 0;
}

int dequeue(struct queue *queue)
{
	int ret = INT_MIN;
	struct node *pnode = queue->front;

	if(pnode) {
		ret = pnode->data;
		queue->front = pnode->next;
		if(queue->front == NULL) {
			queue->rear = NULL;
		}
		free(pnode);
		queue->length--;
	}
	else {
		puts("empty queue");
	}

	return ret;
}

int front(struct queue *queue)
{
	int retval = INT_MIN;
	if(queue && queue->front) {
		retval = queue->front->data;
	}
	return retval;
}

int rear(struct queue *queue)
{
	int retval = INT_MIN;
	if(queue && queue->rear) {
		retval = queue->rear->data;
	}
	return retval;
}

int is_empty(struct queue *queue)
{

	return queue->front==NULL?1:0;
}

int length(struct queue *queue)
{
	return queue->length;
}

int main(int argc, char** argv)
{
	int x;

	struct queue queue;
	init(&queue);

	enqueue(&queue, 0);
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	puts("-----------------------");

	enqueue(&queue, 1);
	enqueue(&queue, 2);
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	puts("-----------------------");

	enqueue(&queue, 3);
	enqueue(&queue, 4);
	enqueue(&queue, 5);
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	puts("-----------------------");

	enqueue(&queue, 6);
	enqueue(&queue, 7);
	enqueue(&queue, 8);
	enqueue(&queue, 9);
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	printf("%d\n", dequeue(&queue));
	puts("-----------------------");

	return 0;
}

