#include <stdio.h>

void output(int* arry, size_t len)
{
	int i = 0;
	for(i=0; i<len; i++) {
		printf("%2i ", arry[i]);
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

void quick_sort_1(int* arry, int low, int high)
{
	int i,j,pivot;
	if( low < high ) {
		i = low;
		j = high;
		pivot = arry[i];
		while( i < j ) {
			while( arry[j] > pivot && j > i) j--;
			arry[i++] = arry[j];
			while( arry[i] < pivot && i < j) i++;
			arry[j--] = arry[i];
		}
		arry[i] = pivot;
		quick_sort_1(arry, low, i-1);
		quick_sort_1(arry, j+1, high);
	}
	return ;
}

void quick_sort_2(int* arry, int low, int high)
{
	int i,j,pivot;
	if(low < high) {
		i = low;
		j = high;
		pivot = arry[j/2];
		while( i < j ) {
			while( i<j && arry[i] < pivot ) i++;
			arry[j/2] = arry[i];
			while( i<j && arry[j] > pivot ) j--;
			arry[i] = arry[j];
		}
		arry[j] = pivot;
		quick_sort_2(arry, low, i-1);
		quick_sort_2(arry, j+1, high);
	}
	return ;
}

int main(int argc, char** argv)
{
	int arry[] = {2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(arry)/sizeof(arry[0]);

	output(arry, len);

	//quick_sort_2(arry, 0, len-1);
	quicksort_iterative(arry, len-1);

	output(arry, len);

	return ;
}
