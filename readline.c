#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define LINE_LENGTH 32

void usage(const char* args)
{
	printf("%s filename\n", args);
}

int readline(int fd, char* buffer, size_t len)
{
	int i, ret = 0;

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
		if(i == ret) {
			ret = 0;
			printf("length[%zu] is too short to read line\n", len);
			lseek(fd, -ret, SEEK_CUR);
		}
	}

	return ret;
}

int main(int argc, char** argv)
{
	int fd;
	int ret = 0;
	char buff[LINE_LENGTH + 1] = {0};

	if(argc < 2) {
		usage(argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0) {
		perror("open");
		return 2;
	}

	while( (ret = readline(fd, buff, LINE_LENGTH)) > 0) {
		buff[ret+1] = 0;
		printf("%s", buff);
	}

	close(fd);
	return ret;
}
