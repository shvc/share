/*
 * Copy a file to another file, just like cp
 * Sun Jan  8 11:30:41 CST 2017
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define LENGTH 1024
/*
struct stat {
	dev_t     st_dev;    
	ino_t     st_ino;   
	mode_t    st_mode; 
	nlink_t   st_nlink; 
	uid_t     st_uid;  
	gid_t     st_gid;  
	dev_t     st_rdev; 
	off_t     st_size; 
	blksize_t st_blksize;  
	blkcnt_t  st_blocks;  

	struct timespec st_atim; 
	struct timespec st_mtim;
	struct timespec st_ctim;

#define st_atime st_atim.tv_sec 
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
*/

void usage(const char* args)
{
	printf("%s filename\n", args);
}

int stat_file(const char* filename)
{
	int ret;
	struct stat st;

	ret = stat(filename, &st);
	if(ret < 0) {
		perror("fstat");
		return 1;
	}
	printf("ino    : %lu\n", st.st_ino);
	printf("size   : %ld\n", st.st_size);
	printf("blksize: %ld\n", st.st_blksize);
	printf("blocks : %ld\n", st.st_blocks);

	return 0;
}

int main(int argc, char** argv)
{
	int ret = 0;

	if(argc == 2) {
		ret = stat_file(argv[1]);
	}
	else {
		usage(argv[0]);
	}

	return ret;
}
