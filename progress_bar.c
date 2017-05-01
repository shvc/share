#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define LEN 102

int main(int argc, char** argv)
{
	int i = 0;
	char bar[LEN];
	char str[] = "|\\-/";

	memset(bar, 0, sizeof(bar));

	for( i=0; i<LEN; i++ ) {
		bar[i] = '#';
		printf("[%-101s][%d%%][%c]\r", bar, i, str[i%4]);
		fflush(stdout);
		usleep(100000);
	}

	printf("\n");
	return 0;
}
