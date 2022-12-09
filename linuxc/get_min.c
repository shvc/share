#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Given an integer X, design an algorithm to find the integer Y that is just larger than X
 * and Y only consisting of digit 3 and 5
 *
 */
int validatey(int y)
{
	int tmp, retval = 1;
	while(y) {
		tmp = y%10;
		if(tmp != 3 && tmp != 5) {
			retval = 0;
			break;
		}
		y /= 10;
	}

	return retval;
}

int validate(int x, int y)
{
	int ret = 0, i;

	for(i = x; i<y; i++) {
		if(validatey(i)) {
			ret = i;
			break;
		}
	}

	return ret;
}

int get_min(int x)
{
	int ret = 0;
	int loc = 1;
	int m   = 0;

	if( x < 3 ) {
		ret = 3;
	}
	else if( x < 5) {
		ret = 5;
	}
	else if(x < 33) {
		ret = 33;
	}
	else {

		while( x>10 ) {
			m = x%10;
			if( m >0 && m <=3) {
				ret += loc*3;
			}
			else {
				ret += loc*5;
			}
			loc *= 10;
			x/=10;
		}

		if( x >0 && x <= 3) {
			ret = ret + loc*3;
		}
		else if( x>3 && x<=5) {
			ret = ret + loc*5;
		}
		else {
			ret = ret + loc*33;
		}
	}

	return ret;
}

void test()
{
	assert(3 == get_min(2));
	assert(5 == get_min(3));
	assert(33 == get_min(5));
	assert(33 == get_min(23));
	assert(33 == get_min(32));
	assert(35 == get_min(33));
	assert(53 == get_min(35));
	assert(333 == get_min(123));
	assert(333 == get_min(321));
	assert(553 == get_min(543));
}

int main(int argc, char** argv)
{
	int x = 3;

	if(argc > 1) {
		x = atoi(argv[1]);
	}
	else {
		test();
	}


	printf("x: %d\n", x);
	printf("y: %d\n", get_min(x));

	printf("validate 321: %d\n", validate(321, get_min(321)));

	return 0;
}

