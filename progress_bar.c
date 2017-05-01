#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

#define LEN 1024

int main(int argc, char** argv)
{
	int i = 0;
	char bar[LEN];
	char str[] = "|\\-/";
	struct winsize w;

	memset(bar, 0, sizeof(bar));
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	for( i=0; i<w.ws_col-2; i++ ) {
		bar[i] = '#';
		printf("[%-104s][%d%%][%c]\r", bar, i, str[i%4]);
		fflush(stdout);
		usleep(100000);
	}

	printf("\n");
	return 0;
}
