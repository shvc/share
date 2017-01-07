#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define LENGTH 64

void usage(const char* args)
{
	printf("%s src_filename dst_filename\n", args);
}

int copy_file(const char* src, const char* dst)
{
	int ret = 0;
	int fd1, fd2;
	struct stat st;
	char buffer[LENGTH];

	fd1 = open(src, O_RDONLY);
	if(fd1 < 0) {
		perror("open");
		return 1;
	}
	ret = fstat(fd1, &st);
	if(ret < 0) {
		perror("fstat");
		close(fd1);
		return 2;
	}

	fd2 = open(dst, O_CREAT|O_TRUNC|O_WRONLY, st.st_mode);
	if(fd2 < 0) {
		perror("open");
		close(fd1);
		return 3;
	}
	
	while( (ret = read(fd1, buffer, LENGTH)) > 0) {
		if(write(fd2, buffer, ret) < ret) {
			perror("write");
			break;
		}
	}

	return ret;
}

int main(int argc, char** argv)
{
	int ret = 0;

	if(argc < 2) {
		usage(argv[0]);
	}
	else {
		ret = copy_file(argv[1], argv[2]);
	}

	return ret;
}
