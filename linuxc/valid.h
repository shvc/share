/*
 *
 */
#ifndef __VALID_H__
#define __VALID_H__
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <error.h>
#include <stdio.h>
#include <string.h>


#define MAGIC_STR  "NSFOCUS"
#define MAGIC_HASH "NSFOCUS_18151"
#define FLAG_LEN   27
#define HASH_LEN   33

struct dev_flag
{
	int mgd;
	char flag[FLAG_LEN];
	char hash[HASH_LEN];
};

struct dev_data
{
	int status;
	struct sockaddr_in ipaddr;
	struct sockaddr_in netmask;
	struct sockaddr_in gateway;
};

int write_data(const char *filename, off_t pos, const struct dev_data *data);
#endif
