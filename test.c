#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cnt = 0;

int fib(int n)
{
	cnt++;
	if(0 == n)
		return 1;
	else if(1 == n)
		return 2;
	else
		return fib(n-1) + fib(n-2);
}

int func1(long x)
{
	int ret = 0;
	if(x&(x-1)) {
		ret = 0;
	} else {
		ret = 1;
	}
	return ret;
}

int func2(long x)
{
	int i, ret = 0;
	unsigned char j;
	union {
		long x;
		unsigned char y[sizeof(long)];
	} data;
	data.x = x;
	for(i=0; i<sizeof(long); i++) {
		j = data.y[i];
		if(j==1 || j==2 || j==4 || j==8 || j==16 || j==32 || j==64 || j==128) {
			ret++;
		} else if(j != 0) {
			ret = 2;
		}
	}
	return 1==ret;
}

void test(int *p)
{
	p = malloc(sizeof(int)*9);

	return ;
}

int main(int argc, char* argv[])
{
	int *p, array[10];
	long d;
	if(argc == 2) {
		d = atol(argv[1]);
	} else {
		printf("input a number:");
		scanf("%ld", &d);
	}
	printf("number: %ld\n", d);

	printf("func1 return: %d\n", func1(d));
	printf("func2 return: %d\n", func2(d));

	fib(8);
	printf("cnt: %d\n", cnt);

	printf("strlen: %lu\n", strlen("abc\101\0fghijk\0"));
	
	p = malloc(100);
	test(p);

	array[10] = 9;
	return 0;
}

