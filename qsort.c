#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ARRAY_LEN 32

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

void swap(int* x, int *y)
{
	if(x != y) {
		*x = *x ^ *y;
		*y = *x ^ *y;
		*x = *x ^ *y;
	}
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

int partition(int *array, int l, int h)
{
	int pivot;

	if( l < h) {
		pivot = array[(h-l)/2];
		for( ; ; l++, h--) {
			while( array[l] < pivot ) l++;
			while( array[h] > pivot ) h--;
			if (l >= h) break;
			swap(array+l, array+h);
		}
	}
	return l;
}

int partition2(int *array, int l, int h)
{
	int i,j;
	i = l-1;

	for ( j=l; j<h; j++ ) {
		if ( array[j] < array[h] ) {
			i++;
			swap(array+i, array+j);
		}
	}
	
	swap(array+i+1, array+h);

	return i+1;
}

void quicksort_1(int* array, int len)
{
	int l, h, pivot;
	if( len > 1 ) {
		pivot = array[len/2];
		for(l=0, h=len-1; ; l++, h--) {
			while( array[l] < pivot ) l++;
			while( array[h] > pivot ) h--;
			if (l >= h) break;
			swap(array+l, array+h);
		}
		quicksort_1(array, l);
		quicksort_1(array+l, len-l);
	}
	return ;
}

void quicksort_2(int* array, int low, int high)
{
	int k = 0;
	if(low < high) {
		k = partition2(array, low, high);
		quicksort_2(array, low, k-1);
		quicksort_2(array, k+1, high);
	}
	return ;
}

void quicksort_iterative(int* array, int len)
{
	int stack[64];
	int top = -1;
	int l = 0, h = len-1, m;

	stack[++top] = l;
	stack[++top] = h;

	while( top >= 0) {
		h = stack[top--];
		l = stack[top--];
		m = partition2(array, l, h);
		if ( l < m-1 ) {
			stack[++top] = l;
			stack[++top] = m-1;
		}

		if ( m+1 < h ) {
			stack[++top] = m+1;
			stack[++top] = h;
		}
	}
}
int main(int argc, char** argv)
{
	int array[ARRAY_LEN] = {2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(array)/sizeof(array[0]);

	srandom(time(NULL));

	init(array, len, 100);
	output(array, len);
	quicksort_1(array, len);
	validate(array, len);
	output(array, len);
	puts("----------------------------");

	init(array, len, 100);
	output(array, len);
	quicksort_2(array, 0, len-1);
	validate(array, len);
	output(array, len);
	puts("----------------------------");

	init(array, len, 100);
	output(array, len);
	quicksort_iterative(array, len);
	validate(array, len);
	output(array, len);
	puts("----------------------------");

	return 0;
}

