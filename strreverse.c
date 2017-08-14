#include <stdio.h>

char* strreverse(char* str, size_t len)
{
	char* p = str;
	char* q = str + len -1;

	if(NULL == str) return str;

	while(p < q) {
		*p = *p ^ *q;
		*q = *p ^ *q;
		*p = *p ^ *q;
		p++;
		q--;
	}

	return str;
}


int main(int argc, char** argv)
{
	char a[] = "abc1234efg";

	printf("bef: %s\n", a);
	printf("len: %ld\n", sizeof(a)/sizeof(a[0]));
	strreverse(a, sizeof(a)/sizeof(a[0])-1);
	printf("aft: %s\n", a);
	strreverse(a, sizeof(a)/sizeof(a[0])-1);
	printf("aft: %s\n", a);

	return 0;
}

