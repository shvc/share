#include <stdio.h>

#define LEN 150

int count(int *lights, size_t len)
{
	int i, num = 0;
	for(i=0; i<len; i++) {
		if(lights[i]) {
			num++;
		}
	}

	return num;
}


int main()
{
	int i;
	int lights[LEN] = {0};

	for(i=0; i<LEN; i++) {
		lights[i] = 1;
	}
	printf("begin 0: %d\n", count(lights, LEN));

	for(i=0; i<LEN; i++) {
		if(i%3 == 0) {
			if(lights[i] == 1) {
				lights[i] = 0;
			}
			else {
				lights[i] = 1;
			}
		}
	}
	printf("begin 1: %d\n", count(lights, LEN));

	for(i=0; i<LEN; i++) {
		if(i%5 == 0) {
			if(lights[i] == 1) {
				lights[i] = 0;
			}
			else {
				lights[i] = 1;
			}
		}
	}
	printf("begin 2: %d\n", count(lights, LEN));


	return 0;
}

