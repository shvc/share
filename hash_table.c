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

struct data_item* search(struct data_item* hash[SIZE], int key)
{
	struct data_item *item = NULL;
	int hash_index = hash_code(key);
	
	while(hash[hash_index] != NULL) {
		if(hash[hash_index]->key == key) {
			item =  hash[hash_index];
			break;
		}
		hash_index++;
		hash_index%=SIZE;
	}
	return item;
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
	int hash_index = hash_code(key);
	
	while(hash[hash_index] != NULL) {
		if(hash[hash_index]->key == key) {
			free(hash[hash_index]);
			hash[hash_index] == NULL;
		}
		hash_index++;
		hash_index%=SIZE;
	}
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

void hash_free(struct data_item **hash)
{
	int i;
	for(i=0; i<SIZE; i++) {
		if(hash[i]) {
			free(hash[i]);
			hash[i] = NULL;
		}
	}
}

int main(int argc, char** argv)
{
	struct data_item* pitem = NULL;
	struct data_item* hash[SIZE] = {NULL};

	traveral(hash);
	insert(hash, 2, 202);
	insert(hash, 2, 203);
	insert(hash, 2, 204);
	insert(hash, 3, 303);
	insert(hash, 4, 404);
	traveral(hash);

	pitem = search(hash, 2);
	if(pitem) {
		printf("get hash[%d]: %d\n", pitem->key, pitem->data);
	}

	pitem = search(hash, 3);
	if(pitem) {
		printf("get hash[%d]: %d\n", pitem->key, pitem->data);
	}

	pitem = search(hash, 4);
	if(pitem) {
		printf("get hash[%d]: %d\n", pitem->key, pitem->data);
	}

	return 0;
}

