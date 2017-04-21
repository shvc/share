#include <stdio.h>

int print(int *arry, size_t len)
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
	int arry[] = {1, 2, 3, 2, 1, 3, 1, 2};
	print(arry, sizeof(arry)/sizeof(arry[0]));
	ret = findodd(arry, sizeof(arry)/sizeof(arry[0]));

	printf("result: %d\n", ret);


	return ret;
}

