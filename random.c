#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	int count = 10;

	while(count--) {
		printf("%d\n", rand());
	}

	return 0;
}
