#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

#define ARRAY_LEN 32

/*
 * (key - low)/(a[key] - a[low]) = (high - low)/(a[high] - a[low])
 * key = low + (high - low)/(a[high] - a[low]) * (a[key] - a[low])
 */

int interpolation_search(int *array, size_t len, int x)
{
	int index = -1;
	int low, high, pivot;

	low = 0;
	high = len - 1;
	
	while( low <= high) {
		pivot = low + (high - low)/(array[high] - array[low]) *(x - array[low]);
		if(array[pivot] == x) {
			index = pivot;
			break;
		}
		else if(array[pivot] < x) {
			low = pivot + 1;
		}
		else {
			high = pivot - 1;
		}
	}

	return index;
}

void init(int* array, size_t len, int round)
{
	int i;
	for(i=0; i<len; i++) {
		array[i] = random()%round;
	}
}

void output(int* array, size_t len)
{
	int i = 0;
	for(i=0; i<len; i++) {
		printf("%2i ", array[i]);
	}

	puts("");
	return ;
}

int validate(int *array, size_t len)
{
	int i,j;
	for(i=0; i<len; i++) {
		for(j=0; j<i; j++) {
			if(array[i] < array[j]) {
				printf("failed, array[%d]=%d < array[%d]=%d\n", i, array[i], j, array[j]);
				return 1;
			}
		}
	}
	return 0;
}

void quick_sort(int* array, int len)
{
	int i,j,pivot;
	if( len < 2 ) {
		return ;
	}
	pivot = array[len/2];
	for(i=0, j=len-1; ; i++, j--) {
		while( array[i] < pivot ) i++;
		while( array[j] > pivot ) j--;
		if (i >= j) break;
		array[i] = array[i] ^ array [j];
		array[j] = array[i] ^ array [j];
		array[i] = array[i] ^ array [j];
	}

	quick_sort(array, i);
	quick_sort(array+i, len-i);
}

int test(int* array, size_t len)
{
	int key, skey;

	key = random()%len;
	printf("array[%d] = %d\n", key, array[key]);

	skey = interpolation_search(array, len, array[key]);
	printf("array[%d] = %d\n", skey, array[skey]);

	assert(-1 == skey || array[skey] == array[key]);

	return 0;
}

int main(int argc, char** argv)
{
	int array[ARRAY_LEN] = {2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(array)/sizeof(array[0]);
	srandom(time(NULL));

	init(array, len, 100);
	output(array, len);
	quick_sort(array, len);
	validate(array, len);
	output(array, len);
	test(array, len);
	puts("----------------------------");

	init(array, len, 100);
	output(array, len);
	quick_sort(array, len);
	validate(array, len);
	output(array, len);
	test(array, len);
	puts("----------------------------");

	init(array, len, 100);
	output(array, len);
	quick_sort(array, len);
	validate(array, len);
	output(array, len);
	test(array, len);
	puts("----------------------------");

	return 0;
}

