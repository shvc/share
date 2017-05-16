#include <stdio.h>

struct hlist_head {
	struct hlist_node *head;
};

struct hlist_node {
	struct hlist_node *next;
	struct hlist_node **pprev;
};

void hlist_add_entry(struct hlist_head* head)
{
}

void hlist_delete_entry(struct hlist_node *entry)
{
	struct hlist_node *next = entry->next;
	struct hlist_node **pprev = entry->pprev;
	
	*pprev = next;
	if(next) {
		next->pprev = pprev;
	}
}


int main(int argc, char **argv)
{
	int retval = 0;

	struct hlist_head head;
	head.head = NULL;


	return retval;
}
