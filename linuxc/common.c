#include "valid.h"

/*
 * write ipaddr and netmaks to file
 */
int write_data(const char *filename, off_t pos, const struct dev_data *data)
{
	int ret = 0;
	int  fd = 0;

	if(NULL == filename || NULL == data) {
		return 1;
	}

	fd = open(filename, O_WRONLY);
	if(fd < 0) {
		perror(filename);
		return 2;
	}

	ret = pwrite(fd, data, sizeof(struct dev_data), pos);
	if(ret < 0) {
		perror("write");
	}
	close(fd);
	ret = 0;
	return ret;
}

