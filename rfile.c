#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FILE_NAME "/tmp/test.tmp"

int main(int argc, char** argv)
{
	int revl = 0;
	int i    = 0;
	int fd   = 0;
	char filename[64];
	char buffer[128];

	if(argc > 1) {
		strcpy(filename, argv[1]);
	}
	else {
		strcpy(filename, FILE_NAME);
	}

	printf("file: %s\n", filename);
	fd = open(filename, O_RDONLY);
	if(fd < 0) {
		perror("open");
		return 1;
	}

	for(i=0; i<600; i++ ) {
		revl = read(fd, buffer, 127);
		if(revl < 0) {
			perror("write");
			break;
		}
		buffer[revl] = 0;
		printf("%s", buffer);
		sleep(1);
	}

	close(fd);
	return revl;
}
