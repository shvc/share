#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ARRAY_LEN 32

void init(int* array, size_t len, int round)
{
	int i;
	srandom(time(NULL));
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

void quicksort_iterative(int array[], unsigned len)
{
	int pivot;
	unsigned right, left = 0, stack[64], pos = 0, seed = rand();
	for ( ; ; ) {                                                          /* outer loop */
		for (; left+1 < len; len++) {                          /* sort left to len-1 */
			if (pos == 64) len = stack[pos = 0];       /* stack overflow, reset */
			pivot = array[left+seed%(len-left)];       /* pick random pivot */
			seed = seed*69069+1;                     /* next pseudorandom number */
			stack[pos++] = len;                         /* sort right part later */
			for (right = left-1; ; ) {      /* inner loop: partitioning */
				while (array[++right] < pivot);  /* look for greater element */
				while (pivot < array[--len]);    /* look for smaller element */
				if (right >= len) break;           /* partition point found? */
				array[right] = array[right] ^ array[len];
				array[len]   = array[right] ^ array[len];
				array[right] = array[right] ^ array[len];
			}                            /* partitioned, continue left part */
		}
		if (pos == 0) break;                               /* stack empty? */
		left = len;                             /* left to right is sorted */
		len = stack[--pos];                      /* get next range to sort */
	}
}

void quick_sort_1(int* array, int len)
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

	quick_sort_1(array, i);
	quick_sort_1(array+i, len-i);
}

void quick_sort_2(int* array, int low, int high)
{
	int i, j, pivot;
	if(low < high) {
		i = low;
		j = high;
		pivot = array[j];
		while( i < j ) {
			while( i<j && array[i] < pivot ) i++;
			if(i<j)
				array[j] = array[i];
			while( i<j && array[j] > pivot ) j--;
			if(i<j) {
				array[i] = array[j];
			}
		}
		array[j] = pivot;
		quick_sort_2(array, low, i-1);
		quick_sort_2(array, j+1, high);
	}
	return ;
}

int main(int argc, char** argv)
{
	int array[ARRAY_LEN] = {2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(array)/sizeof(array[0]);

	init(array, len, 100);
	output(array, len);
	quick_sort_1(array, len);
	validate(array, len);
	output(array, len);
	puts("----------------------------");
	sleep(1);

	init(array, len, 100);
	output(array, len);
	//quick_sort_2(array, 0, len-1);
	quick_sort_1(array, len);
	validate(array, len);
	output(array, len);
	puts("----------------------------");
	sleep(1);

	init(array, len, 100);
	output(array, len);
	quicksort_iterative(array, len);
	validate(array, len);
	output(array, len);
	puts("----------------------------");

	return 0;
}

