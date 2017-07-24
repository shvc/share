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

	quick_sort_2(arry, 0, len);

	output(arry, len);

	return ;
}
