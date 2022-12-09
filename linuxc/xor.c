#include <stdio.h>

void output(int *arry, size_t len)
{
	int i;
	for(i=0; i<len; i++) {
		printf("%d ", arry[i]);
	}
	printf("\n");
}

int findodd(int *arry, size_t len)
{
	int i, ret = arry[0];
	for(i=1; i<len; i++ ) {
		ret = ret ^ arry[i];
	}

	return ret;
}

int main(int argc, char** argv)
{
	int ret = 0;
	int arry[] = {3, 2, 3, 5, 1, 3, 1, 2, 5};
	size_t len = sizeof(arry)/sizeof(arry[0]);
	output(arry, len);
	ret = findodd(arry, len);

	printf("result: %d\n", ret);

	return ret;
}

