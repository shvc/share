#include <stdio.h>
#include <stdlib.h>

/*
 * Given a positive integer n, find the least number of perfect square numbers.
 * for example, 1,4,9,16,25,...
 * Given n=12, return 3 because 12=4+4+4
 * Given n=13, return 2 because 13=9+4
 */

int min(int x, int y) 
{
	return x<y?x:y;
}

int get_least_square_num(size_t num)
{
	int i, s;
	int retval = num;
	if( num <= 3) return num;

	for(i=1; i<=num; i++) {
		s = i*i;
		if(s > num) {
			break;
		}
		else {
			retval = min(retval, 1+get_least_square_num(num-s));
		}
	}

	return retval;
}

int main(int argc, char** argv)
{
	int cnt;
	size_t num = 99;
	
	if(argc > 1) {
		num = atoi(argv[1]);
	}

	cnt = get_least_square_num(num);

	printf("number: %d, cnt: %d\n", num, cnt);

	return 0;
}
