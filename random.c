#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void random1(int length, int size)
{
	int i;
	for(i=0; i<length; i++) {
		printf("%d ", rand()%size);
	}
	puts("");
}

void random2(int length, int size)
{
	int i;
	srandom(time(NULL));

	for(i=0; i<length; i++) {
		printf("%ld ", random()%size);
	}
	puts("");
}

int main(int argc, char** argv)
{
	int length = 10;
	random1(length, 100);
	random2(length, 100);


	return 0;
}
