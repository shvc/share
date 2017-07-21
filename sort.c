#include <stdio.h>

void output(int* a, size_t len)
{
	int i;
	for(i=0; i<len; i++) {
		printf("%2d ", a[i]);
	}
	puts("");
	return;
}

int* bubble_sort(int* a, size_t len)
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
	return a;
}

int* optimized_bubble_sort(int* a, size_t len)
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
	return a;
}

int* select_sort(int* a, size_t len)
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
	return a;
}

int* optimized_select_sort(int* a, size_t len)
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
	return a;
}


int main(int argc, char** argv)
{
	int arry[] = {2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(arry)/sizeof(arry[0]);

	output(arry, len);
	optimized_select_sort(arry, len);
	output(arry, len);
	optimized_bubble_sort(arry, len);
	output(arry, len);
	bubble_sort(arry, len);
	output(arry, len);

	return 0;
}

