/*
 *
 */
#include "valid.h"

/*
 * Find the position of the flag in given filename
 */
off_t find_pos(const char *filename, const struct dev_flag *data)
{
	off_t pos = 0;
	off_t i   = 0;
	int fd    = 0;
	int  ret  = 0;
	int flag  = 0;
	struct dev_flag buf;

	if(NULL == filename) {
		pos = -1;
		return pos;
	}

	fd = open(filename, O_RDONLY);
	if(-1 == fd) {
		perror(filename);
		pos = -2;
		return pos;
	}

	for(i=0; i<0xffff; i++) {
		pos = lseek(fd, i, SEEK_SET);
		ret = read(fd, &buf, sizeof(struct dev_flag));
		if(ret < 0) {
			pos = -3;
			break;
		}
		if(0 == strcmp(data->flag, buf.flag) && 0 == strcmp(data->hash, buf.hash)) {
			flag = 1;
			break;
		}
	}

	if(0 == flag) {
		pos = -4;
	}

	return pos;
}


int main(int argc, char* argv[])
{
	int ret = 0;
	off_t pos = 0;
	struct dev_flag dflag;
	struct dev_data ddata;

	char ipaddr[]  = "192.168.111.222";
	char netmask[] = "255.255.000.000";
	char gateway[] = "192.168.111.111";

	if(argc < 2) {
		printf("usage: %s filename ip mask gateway\n", argv[0]);
		return 1;
	} else if(argc == 2) {
		printf("use default ip mask gateway\n");
	} else if(argc == 5) {
		if(strlen(argv[2]) < strlen(ipaddr)) {
			strcpy(ipaddr, argv[2]);
		} else {
			printf("ip address lenth error\n");
			return 1;
		}

		if(strlen(argv[3]) < strlen(netmask)) {
			strcpy(netmask, argv[3]);
		} else {
			printf("ip netmask lenth error\n");
			return 1;
		}

		if(strlen(argv[4]) < strlen(gateway)) {
			strcpy(gateway, argv[4]);
		} else {
			printf("ip gateway lenth error\n");
			return 1;
		}
	} else {
		printf("usage: %s filename ip mask gateway\n", argv[0]);
	}


	/* prepare data */
	memset(&dflag, 0, sizeof(struct dev_flag));
	memset(&ddata, 0, sizeof(struct dev_data));
	if(strlen(MAGIC_STR) < FLAG_LEN) {
		strcpy(dflag.flag, MAGIC_STR);
	} else {
		printf("%s too long\n", MAGIC_STR);
		return 2;
	}
	if(strlen(MAGIC_HASH) < HASH_LEN) {
		strcpy(dflag.hash, MAGIC_HASH);
	} else {
		printf("%s too long\n", MAGIC_HASH);
		return 2;
	}

	printf("flag: %s\n", dflag.flag);
	printf("hash: %s\n", dflag.hash);

	pos = find_pos(argv[1], &dflag);
	if(pos) {
		printf("can not find pos: %d\n", pos);
		return 3;
	}
	ddata.status  = 1;

	if(inet_aton(ipaddr, &(ddata.ipaddr.sin_addr)) < 0) {
		perror(ipaddr);
		return 4;
	}
	if(inet_aton(netmask, &(ddata.netmask.sin_addr)) < 0) {
		perror(netmask);
		return 4;
	}
	if(inet_aton(gateway, &(ddata.gateway.sin_addr)) < 0) {
		perror(gateway);
		return 4;
	}

	printf("status : %d\n", ddata.status);
	printf("ipaddr : %s\n", inet_ntoa(ddata.ipaddr.sin_addr));
	printf("netmask: %s\n", inet_ntoa(ddata.netmask.sin_addr));
	printf("gateway: %s\n", inet_ntoa(ddata.gateway.sin_addr));
	ret = write_data(argv[1], pos+sizeof(struct dev_flag), &ddata);
	printf("write_data ret: %d\n", ret);

	return ret;
}
