#include <stdio.h>
#include <assert.h>

/*
 * Given an integer X, design an algorithm to find the nteger Y that is just larger than X
 * and Y only consisting of digit 3 and 5
 *
 */

int get_min(int x)
{
	int ret = 0;
	int loc = 1;

	while( x>10 ) {
		ret *= 10;
		ret += 3;
		loc *= 10;
		x/=10;
	}

	if( x >0 && x < 3) {
		ret = ret + loc*3;
	}
	else if( x>=3 && x<5) {
		ret = ret + loc*5;
	}
	else {
		ret = ret + loc*33;
	}

	return ret;
}

void test()
{
	assert()
}

int main(int argc, char** argv)
{
	int x = 3;

	if(argc > 1) {
		x = atoi(argv[1]);
	}
	else {
		printf("inpu x:");
		scanf("%d", &x);
	}

	printf("x: %d\n", x);
	printf("y: %d\n", get_min(x));

	return 0;
}

