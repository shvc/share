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

int main(int argc, char** argv)
{
	int ret = 0;

	int a[] = {2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(a)/sizeof(a[0]);

	output(a, len);
	select_sort(a, len);
	output(a, len);
	optimized_bubble_sort(a, len);
	output(a, len);
	bubble_sort(a, len);
	output(a, len);

	return ret;
}

