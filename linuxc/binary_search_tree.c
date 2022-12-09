#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *left;
	struct node *right;
};

struct node *root = NULL;


void insert(int data)
{
	struct node *pnode;
	struct node *current;
	struct node *datanode;
	datanode = malloc(sizeof(struct node));
	datanode->data = data;
	datanode->left = NULL;
	datanode->right = NULL;
	if(root == NULL) {
		root = datanode;
	}
	else {
		current = root;
		do {
			pnode = current;
			if( data < current->data) {
				current = current->left;
			}
			else if( data > current->data) {
				current = current->right;
			}
			else {
				printf("node[%d] exist\n", data);
				free(datanode);
				return ;
			}
		} while (current);

		if( NULL == pnode->left ) {
			pnode->left = datanode;
		}
		else {
			pnode->right = datanode;
		}
	
	}
}

struct node* search(int data)
{
	struct node* current = root;

	while( current && current->data != data) {
		printf("search %p: %d\n", current, current->data);
		if(current->data < data ) {
			current = current->right;
		}
		else {
			current = current->left;
		}
	}

	return current;

}

void output(struct node* node)
{
	if(node) {
		printf("%p: %d\n", node, node->data);
	}
}

void preorder_traversal(struct node *root)
{
	if( root ) {
		output(root);
		preorder_traversal(root->left);
		preorder_traversal(root->right);
	}
}


void inorder_traversal(struct node *root)
{
	if( root ) {
		inorder_traversal(root->left);
		output(root);
		inorder_traversal(root->right);
	}
}

void postorder_traversal(struct node *root)
{
	if( root ) {
		postorder_traversal(root->left);
		postorder_traversal(root->right);
		output(root);
	}
}


int main(int argc, char** argv)
{
	struct node *p = NULL;	
	insert(5);
	insert(8);
	insert(3);
	insert(9);
	insert(0);
	printf("---- preorder traversal tree ----\n");
	preorder_traversal(root);
	printf("---- inorder traversal tree ----\n");
	inorder_traversal(root);
	printf("---- postorder traversal tree ----\n");
	postorder_traversal(root);
	

	p = search(8);
	output(p);
	printf("---- search 8 result ----\n");

	p = search(3);
	output(p);
	printf("---- search 3 result ----\n");

	p = search(0);
	output(p);
	printf("---- search 0 result ----\n");

	return 0;
}

