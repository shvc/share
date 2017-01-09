/*
 * Sun Jan  8 22:37:52 CST 2017
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define LINE_LENGTH 32

void usage(const char* args)
{
	printf("%s filename\n", args);
}

ssize_t readline(int fd, char* buffer, size_t len)
{
	int i;
	ssize_t ret = 0;

	ret = read(fd, buffer, len);
	if(ret < 0) {
		perror("read");
	}
	else if(ret > 0) {
		for(i=0; i<ret; i++) {
			if(buffer[i] == '\n') {
				buffer[i+1] = 0;
				lseek(fd, i-ret+1, SEEK_CUR);
				break;
			}
		}
		if(i == ret) { /* len can't reach the end of line */
			lseek(fd, -ret, SEEK_CUR);
			ret = len + 1;
		}
	}

	return ret;
}

int main(int argc, char** argv)
{
	int fd;
	size_t ret = 0;
	size_t len = LINE_LENGTH;

	char *buff = malloc(len);

	if(argc < 2) {
		usage(argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0) {
		perror("open");
		return 2;
	}

	while( (ret = readline(fd, buff, len)) > 0) {
		if(ret <= len) {
			buff[ret+1] = 0;
			printf("%s", buff);
		}
		else { /* bigger size of buff */
			free(buff);
			len *= 2;
			buff = malloc(len);
			if(buff == NULL) {
				break;
			}
		}
	}

	free(buff);
	close(fd);
	return ret;
}
