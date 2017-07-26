#include <stdio.h>
#include <assert.h>

/*
 * Given a positive integer n, find the least number of perfect square numbers.
 * for example, 1,4,9,16,25,...
 * Given n=12, return 3 because 12=4+4+4
 * Given n=13, return 2 because 13=9+4
 */

int isqrt(int n)
{
	int x;
	for( x=1; x*x<=n; x++ );
	return x-1;
}

int get_least_squares_0(size_t num)
{
	int a,b;
	while (num % 4 == 0) num /= 4;
	if (num % 8 == 7) return 4;
	for (a = 0; a * a <= num; ++a) {
		b = isqrt(num - a * a);
		if (a * a + b * b == num) {
			return !!a + !!b;
		}
	}
	return 3;
}

int get_least_squares_1(size_t num)
{
	int i, min;
	int retval = num;

	for(i=2; i*i<=num; i++) {
		min = 1+get_least_squares_1(num-i*i);
		retval = retval < min ? retval : min;
	}

	return retval;
}

void test( int(*fn)(size_t))
{
	assert(1 == fn(1));
	assert(2 == fn(2));
	assert(3 == fn(3));
	assert(1 == fn(4));
	assert(2 == fn(5));
	assert(3 == fn(6));
	assert(4 == fn(7));
	assert(2 == fn(8));
	assert(1 == fn(9));
	assert(2 == fn(10));
	assert(3 == fn(11));
	assert(3 == fn(12));
	assert(2 == fn(13));
	assert(3 == fn(14));
	assert(4 == fn(15));
	assert(1 == fn(16));
}
int main(int argc, char** argv)
{
	int cnt;
	size_t num = 99;

	if(argc > 1) {
		num = atoi(argv[1]);
	}

	cnt = get_least_squares_0(num);
	test(get_least_squares_0);

	printf("number: %d, cnt: %d\n", num, cnt);

	return 0;
}

