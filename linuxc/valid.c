/*
 *
 */
#include <net/route.h>
#include "valid.h"

#define DEV_FILE "/dev/sdc"
/*
 * Valid device
 */
int valid_dev(const char *filename, const struct dev_flag *data)
{
	int ret      = 1;
	int fd       = 0;
	off_t offset = 0;
	struct dev_flag buf;

	if(NULL == filename || NULL == data) {
		return ret;
	}

	fd = open(filename, O_RDWR);
	if(-1 == fd) {
		ret = 2;
		perror(filename);
		return ret;
	}

	ret = read(fd, &buf, sizeof(struct dev_flag));
	if(-1 == ret) {
		close(fd);
		ret = 3;
		perror(filename);
		return ret;
	}


	if(0 != strcmp(data->flag, buf.flag) && 0 != strcmp(data->hash, buf.hash)) {
		offset = lseek(fd, 0, SEEK_SET);
		ret = write(fd, data, sizeof(struct dev_flag));
		if(-1 == ret) {
			ret = 4;
		} else {
			ret = 5;
		}
	} else {
		ret = 0;
	}

	close(fd);
	return ret;
}

/*
 * Read ip, mask, gateway from block device
 */
int read_info(const char *filename, off_t pos, struct dev_data *pdata)
{
	int ret = 0;
	int fd  = 0;

	if(NULL == filename || NULL == pdata) {
		return 1;
	}

	fd = open(filename, O_RDONLY);
	if(fd < 0) {
		perror(filename);
		return 2;
	}

	ret = pread(fd, pdata, sizeof(struct dev_data), pos);
	printf("pread pos: %d, size: %d, ret: %d\n", pos, sizeof(struct dev_data), ret);
	if(ret < 0) {
		ret = 4;
	} else {
		ret = 0;
	}
	close(fd);
	return ret;
}

/*
 * Interface configuration
 */
int ifconfig(const char *ifname, const struct dev_data *pdata)
{
	int ret = 0;
	int fd  = 0;
	struct sockaddr_in *sin = NULL;
	struct ifreq ifr;
	struct rtentry rtn;

	if(NULL == ifname || NULL == pdata) {
		return 1;
	}
	if(1 != pdata->status) {
		return 2;
	}

	fd = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd < 0) {
		perror("socket");
		return 3;
	}

	memset(&ifr, 0, sizeof(struct ifreq));
	strcpy(ifr.ifr_name, ifname);
	sin = (struct sockaddr_in*)&ifr.ifr_addr;
	sin->sin_family = AF_INET;
	/* config ip address */
	memcpy(&(sin->sin_addr), &(pdata->ipaddr.sin_addr), sizeof(struct sockaddr_in));
	ret = ioctl(fd, SIOCSIFADDR, &ifr);
	if(ret < 0) {
		perror("ioctl SIOCSIFADDR");
		close(fd);
		return 4;
	}

	/* config net mask */
	memcpy(&(sin->sin_addr), &(pdata->netmask.sin_addr), sizeof(struct sockaddr_in));
	ret = ioctl(fd, SIOCSIFNETMASK, &ifr);
	if(ret < 0) {
		perror("ioctl SIOCSIFNETMASK");
		close(fd);
		return 5;
	}

	/* config gateway */
	memset(&rtn, 0, sizeof(struct rtentry));
	memset(sin, 0, sizeof(struct sockaddr_in));
	sin->sin_family = AF_INET;
	sin->sin_port = 0;
	memcpy(&(sin->sin_addr), &(pdata->gateway.sin_addr), sizeof(struct sockaddr_in));
	memcpy(&rtn.rt_gateway, sin, sizeof(struct sockaddr_in));
	((struct sockaddr_in*)&rtn.rt_dst)->sin_family = AF_INET;
	((struct sockaddr_in*)&rtn.rt_genmask)->sin_family = AF_INET;
	rtn.rt_flags = RTF_GATEWAY;

	ret = ioctl(fd, SIOCADDRT, &rtn);
	if(ret < 0) {
		perror("ioctl SIOCADDRT");
		close(fd);
		return 6;
	}
	close(fd);
	return ret;
}

int main(int argc, char* argv[])
{
	int ret;
	char filename[64];
	struct dev_flag dflag;
	struct dev_data ddata;

	if(argc > 1) {
		strcpy(filename, argv[1]);
	} else {
		strcpy(filename, DEV_FILE);
	}

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
	ret = valid_dev(filename, &dflag);
	if(ret) {
		printf("valid_dev ret: %d\n", ret);
		if(5 == ret) {
			ret = write_data(filename, sizeof(struct dev_flag), &ddata);
		}
		return 3;
	}
	ret = read_info(filename, sizeof(struct dev_flag), &ddata);
	printf("read_info ret: %d\n", ret);
	printf("status : %d\n", ddata.status);
	printf("ipaddr : %s\n", inet_ntoa(ddata.ipaddr.sin_addr));
	printf("netmask: %s\n", inet_ntoa(ddata.netmask.sin_addr));
	printf("gateway: %s\n", inet_ntoa(ddata.gateway.sin_addr));

	ret = ifconfig("eth0", &ddata);
	printf("ifconfig ret: %d\n", ret);
	return ret;
}
