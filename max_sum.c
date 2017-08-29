#include <stdio.h>

void output(int *array, size_t len)
{
	int i;
	for(i=0; i<len; i++) {
		printf("%2d ", array[i]);
	}
	puts("");
}

int max_sum(int *array, size_t len)
{
	int max = 0, sum = 0, i;

	for( i=0; i<len; i++ ) {
		sum += array[i];
		if(sum > max) {
			max = sum;
		}
		if( sum < 0) {
			sum = 0;
		}
	}

	return max;
}

int main(int argc, char** argv)
{
	int array[] = {-2, 4, -3, 5, -1, 3};
	size_t len = sizeof(array)/sizeof(array[0]);

	output(array, len);
	printf("max: %d\n", max_sum(array, len));

	return 0;
}
