#include <stdio.h>

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

int my_print(int* a, size_t len)
{
	int i;
	for(i=0; i<len; i++) {
		printf("%2d ", a[i]);
	}
	printf("\n");
	return 0;
}

int main(int argc, char** argv)
{
	int ret = 0;

	int a[] = {2,9,4,7,5,3,6,1,8,0};
	size_t len = sizeof(a)/sizeof(a[0]);

	my_print(a, len);
	select_sort(a, len);
	my_print(a, len);
	bubble_sort(a, len);
	my_print(a, len);

	return ret;
}

