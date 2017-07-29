#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN 10

void init(int* array, size_t len)
{
	int i;
	for(i=0; i<len; i++) {
		array[i] = rand()%100;
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
				array[right] = array[right] ^ array[len];             /* the only swap */
				array[len]   = array[right] ^ array[len];             /* the only swap */
				array[right] = array[right] ^ array[len];             /* the only swap */
			}                            /* partitioned, continue left part */
		}
		if (pos == 0) break;                               /* stack empty? */
		left = len;                             /* left to right is sorted */
		len = stack[--pos];                      /* get next range to sort */
	} 
}

void quick_sort_1(int* array, int low, int high)
{
	int i,j,pivot;
	if( low < high ) {
		i = low;
		j = high;
		pivot = array[i];
		while( i < j ) {
			while( array[j] > pivot && j > i) j--;
			array[i++] = array[j];
			while( array[i] < pivot && i < j) i++;
			array[j--] = array[i];
		}
		array[i] = pivot;
		quick_sort_1(array, low, i-1);
		quick_sort_1(array, j+1, high);
	}
	return ;
}

void quick_sort_2(int* array, int low, int high)
{
	int i,j,k, pivot;
	if(low < high) {
		i = low;
		j = high;
		k = (low+high)/2;
		pivot = array[k];
		while( i < j ) {
			while( i<j && array[i] < pivot ) i++;
			if(i<j)
				array[k] = array[i];
			while( i<j && array[j] > pivot ) j--;
			if(i<j) {
				array[i] = array[j];
				k = j;
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

	init(array, len);
	output(array, len);

	quick_sort_2(array, 0, len-1);
	output(array, len);
	quicksort_iterative(array, len);

	output(array, len);

	return 0;
}

