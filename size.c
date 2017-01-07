#include <stdio.h>

#define KL_DECLARE_HOOK(ns, net, name, arg) ret ns##_hook_##name(arg);

struct node {
	struct node *next;
	struct node *prev;
	long data;
	unsigned char map[16];
};


int main(int argc, char** argv)
{
	int retval = 0;

	//printf("size: %lu\n", sizeof(struct node));
	
	KL_DECLARE_HOOK(hrp, int, ssl_verify, const char* username);

	

	return retval;
}
