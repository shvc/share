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
		link->next = head;

		head = link;
	}    
}

struct node * deleteFirst()
{

	struct node *tempLink = head;

	if(head->next == head) {  
		head = NULL;
		return tempLink;
	}     

	head = head->next;

	return tempLink;
}

void printList()
{

	struct node *ptr = head;
	printf("[ ");

	if(head != NULL) {

		while(ptr->next != ptr) {     
			printf("%d ", ptr->data);
			ptr = ptr->next;
		}
	}

	printf(" ]\n");
}

int main(int argc, char** argv)
{
	printf("length0: %d\n", length());
	insertFirst(1);
	printf("length1: %d\n", length());
	insertFirst(2);
	printf("length2: %d\n", length());
	insertFirst(3);
	printf("length3: %d\n", length());
	insertFirst(4);
	printf("length4: %d\n", length());
	insertFirst(5);
	insertFirst(6); 
	insertFirst(7); 

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

