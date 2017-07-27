#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
	int data;
	struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

bool isEmpty()
{
	return head == NULL;
}

int length()
{
	int length = 0;

	if(head == NULL) {
		return 0;
	}
	length = 1;

	current = head->next;

	while(current != head) {
		length++;
		current = current->next;   
	}

	return length;
}

void insertFirst(int data)
{
	struct node *link = malloc(sizeof(struct node));
	link->data = data;

	if (isEmpty()) {
		head = link;
		head->next = head;
	} else {
		link->next = head->next;
		head->next = link;
	}    
}

struct node * deleteFirst()
{

	struct node *tempLink = head;

	if(head->next == head) {  
		head = NULL;
		return tempLink;
	}

	tempLink = head->next;
	head->next = tempLink->next;

	return tempLink;
}

void printList()
{

	struct node *ptr = head;
	printf("[ ");

	if(head != NULL) {

		while(ptr->next != head) {     
			printf("%d ", ptr->data);
			ptr = ptr->next;
		}
	}

	printf(" ]\n");
}

int main(int argc, char** argv)
{
	printf("length: %d\n", length());
	insertFirst(1);
	insertFirst(2);
	insertFirst(3);
	insertFirst(4);
	insertFirst(5);
	insertFirst(6); 
	insertFirst(7); 
	printf("length: %d\n", length());

	printf("Original List: "); 

	printList();

	while(!isEmpty()) {            
		struct node *temp = deleteFirst();
		printf("\nDeleted value:");  
		printf("%d ",temp->data);
	}

	printf("\nList after deleting all items: ");
	printList();   
}

