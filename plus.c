#include <stdio.h>

#define TEST(x)	((x)*(x))

int main()
{
	int a = 5;
	
	int i,j;

	i=TEST(a++);
	j=TEST(++a);

	printf("i=%d\n", i);
	printf("j=%d\n", j);


	return 0;
}
