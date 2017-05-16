#include <stdio.h>

struct hlist_head {
	struct hlist_node *head;
};

struct hlist_node {
	struct hlist_node *next;
	struct hlist_node **pprev;
};


int main(int argc, char **argv)
{
	int retval = 0;

	struct hlist_head head;
	head.head = NULL;


	return retval;
}
