#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void output(int* array, size_t len)
{
	int i;
	for(i=0; i<len; i++) {
		printf("%2i ", array[i]);
	}
	puts("");
	return;
}

void swap(int array[], int i, int j)
{
	array[i] = array[i] ^ array[j];
	array[j] = array[i] ^ array[j];
	array[i] = array[i] ^ array[j];
}

void bubble_sort(int* a, size_t len)
{
	int i,j;
	for(i=1; i<len; i++) {
		for(j=0; j<len-i; j++) {
			if(a[j] < a[j+1]) {
				swap(a, j, j+1);
			}
		}
	}
	return ;
}

void optimized_bubble_sort(int* a, size_t len)
{
	int i,j;
	int swapped;
	for(i=1; i<len; i++) {
		swapped = 0;
		for(j=0; j<len-i; j++) {
			if(a[j] < a[j+1]) {
				swap(a, j, j+1);
				swapped = 1;
			}
		}
		if(0 == swapped) {
			break;
		}
	}
	return ;
}

void select_sort(int* a, size_t len)
{
	int i,j;
	for(i=0; i<len-1; i++) {
		for(j=i+1; j<len; j++) {
			if(a[i] > a[j]) {
				swap(a, i, j);
			}
		}
	}
	return ;
}

void optimized_select_sort(int* a, size_t len)
{
	int i,j;
	int min;
	for(i=0; i<len-1; i++) {
		min = i;
		for(j=i+1; j<len; j++) {
			if(a[min] > a[j]) {
				min = j;
			}
		}
		if(min != i) {
			swap(a, i, min);
		}
	}
	return ;
}

void insert_sort(int* array, size_t len)
{
	int i,j;
	int temp;

	for(i=1; i<len; i++) {
		temp = array[i];
		for(j=i-1; j>=0; j--) {
			if(array[j] > temp) {
				array[j+1] = array[j];
			} 
			else {
				break;
			}
		}
		array[j+1] = temp;
	}

	return ;
}


/* set pivot as low */
void quick_sort_0(int* array, int low, int high)
{
	int i,j,pivot;
	if( low < high ) {
		i = low;
		j = high;
		pivot = array[i];
		while( i < j ) {
			while( array[j] > pivot && j > i) j--;
			if( i < j)
				array[i++] = array[j];
			while( array[i] < pivot && i < j) i++;
			if( i < j)
				array[j--] = array[i];
		}
		array[i] = pivot;
		quick_sort_0(array, low, i-1);
		quick_sort_0(array, j+1, high);
	}
	return ;
}

void quick_sort_1(int* array, int low, int high)
{
	return ;
}

/* set pivot as high */
void quick_sort_2(int* array, int low, int high)
{
	int i,j;
	int pivot;
	if ( low < high ) {
		i = low;
		j = high;
		pivot = array[j];
		while( i<j ) {
			while( i<j && array[i] < pivot ) i++;
			if( i<j )
				array[j--] = array[i];
			while( i<j && array[j] > pivot ) j--;
			if( i<j )
				array[i++] = array[j];
		}
		array[j] = pivot;
		quick_sort_2(array, low, i-1);
		quick_sort_2(array, j+1, high);
	}

}

void quick_sort_3(int* array, int low, int high)
{
	int p, pivot, j;
	if(low < high)
	{
		p=array[low];
		pivot=low;
		for(j=low+1; j<=high; j++) {
			if(array[j]<p ) {
				pivot++;
				swap(array, pivot, j);
			}
		}
		swap(array, pivot, low);
		quick_sort_3(array, low, pivot-1);
		quick_sort_3(array, pivot+1, high);
	}
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

int generate_random(size_t len)
{

	srandom(time(NULL));
	return random()%len;
}

int main(int argc, char** argv)
{
	int array[] = {11,12,13,14,10,2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(array)/sizeof(array[0]);

	output(array, len);
	insert_sort(array, len);
	output(array, len);
	optimized_select_sort(array, len);
	output(array, len);
	optimized_bubble_sort(array, len);
	output(array, len);
	bubble_sort(array, len);

	puts("before quick_sort -------------------------------");
	output(array, len);
	quick_sort_2(array, 0, len-1);
	output(array, len);

	return 0;
}

