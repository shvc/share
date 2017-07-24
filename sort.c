#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void output(int* a, size_t len)
{
	int i;
	for(i=0; i<len; i++) {
		printf("%2i ", a[i]);
	}
	puts("");
	return;
}

void bubble_sort(int* a, size_t len)
{
	int i,j;
	for(i=1; i<len; i++) {
		for(j=0; j<len-i; j++) {
			if(a[j] < a[j+1]) {
				a[j]   = a[j] ^ a[j+1];
				a[j+1] = a[j] ^ a[j+1];
				a[j]   = a[j] ^ a[j+1];
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
				a[j]   = a[j] ^ a[j+1];
				a[j+1] = a[j] ^ a[j+1];
				a[j]   = a[j] ^ a[j+1];
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
				a[i] = a[i] ^ a[j];
				a[j] = a[i] ^ a[j];
				a[i] = a[i] ^ a[j];
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
			a[i]   = a[i] ^ a[min];
			a[min] = a[i] ^ a[min];
			a[i]   = a[i] ^ a[min];
		}
	}
	return ;
}

void insert_sort(int* arry, size_t len)
{
	int i,j;
	int temp;

	for(i=1; i<len; i++) {
		temp = arry[i];
		for(j=i-1; j>=0; j--) {
			if(arry[j] > temp) {
				arry[j+1] = arry[j];
			} 
			else {
				break;
			}
		}
		arry[j+1] = temp;
	}

	return ;
}

void quick_sort(int* arry, int low, int high)
{
	int i,j;
	int pivot;
	if ( low < high ) {
		i = low;
		j = high;
		pivot = arry[j];
		while( i<j ) {
			while( i<j && arry[i] < pivot ) i++;
			arry[j--] = arry[i];
			while( j<j && arry[j] > pivot ) j--;
			arry[i++] = arry[j];
		}
		arry[j] = pivot;
		quick_sort(arry, low, i-1);
		quick_sort(arry, j-1, high);
	}

}

int generate_random(size_t len)
{

	srandom(time(NULL));
	return random()%len;
}

int main(int argc, char** argv)
{
	int arry[] = {11,12,13,14,10,2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(arry)/sizeof(arry[0]);

	output(arry, len);
	insert_sort(arry, len);
	output(arry, len);
	optimized_select_sort(arry, len);
	output(arry, len);
	optimized_bubble_sort(arry, len);
	output(arry, len);
	bubble_sort(arry, len);
	output(arry, len);

	quick_sort(arry, 0, len);
	output(arry, len);

	return 0;
}

