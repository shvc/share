#include <stdio.h>
#include <stdlib.h>

#define SIZE 32

struct data_item {
	int data;
	int key;
};

int hash_code(int key)
{
	return key%SIZE;
}

struct data_item search(int key)
{
	int hash_index = hash_code(key);

}

void insert(struct data_item* hash[SIZE], int key, int data)
{
	int hash_index = hash_code(key);
	struct data_item *item = malloc(sizeof(struct data_item));
	item->key = key;
	item->data = data;
	
	while( hash[hash_index] != NULL) {
		++hash_index;
		hash_index %= SIZE;
	}
	hash[hash_index] = item;
}

void delete(struct data_item* hash[SIZE], int key)
{
}

void traveral( struct data_item* hash[SIZE])
{
	int i = 0;
	if(NULL == hash) {
		return;
	}
	for(i=0; i<SIZE; i++) {
		if(hash[i]) {
			printf("hash[%d][%d]: %d\n", i, hash[i]->key, hash[i]->data);
		}
	}
}

int main(int argc, char** argv)
{
	struct data_item* hash[SIZE] = {NULL};

	traveral(hash);
	insert(hash, 2, 288);
	insert(hash, 2, 299);
	traveral(hash);

	return 0;
}
