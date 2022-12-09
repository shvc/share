#include <stdio.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <string.h>
#include <openssl/md5.h>


/*
 * Get mac address, do not use name "eth0", "eth1" ...
 * @str: store mac address
 * Return: success 0
 */
int get_mac(unsigned char* str)
{
	int ret = 0;
	struct ifreq ifr;
	struct ifconf ifc;
	struct ifreq buf[6];
	int success = 0;
	int sock = 0;

	if(NULL == str) {
		return 4;
	}
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) { 
		/* handle error*/ 
		return 1;
	};

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = (__caddr_t)buf;
	if (ioctl(sock, SIOCGIFCONF, &ifc) == -1) { 
		/* handle error */ 
		close(sock);
		return 2;
	}


	struct ifreq* it = ifc.ifc_req;
	const struct ifreq* const end = it + (ifc.ifc_len / sizeof(struct ifreq));

	for (; it != end; ++it) {
		strcpy(ifr.ifr_name, it->ifr_name);
		if (ioctl(sock, SIOCGIFFLAGS, &ifr) == 0) {
			if (! (ifr.ifr_flags & IFF_LOOPBACK)) { /* don't count loopback */
				if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
					success = 1;
					break;
				}
			}
		} else { 
			/* handle error */
			break;
		}
	}
	close(sock);

	if (success) {
		ret = 0;
		memcpy(str, ifr.ifr_hwaddr.sa_data, 6);
	} else {
		ret = 3;
	}

	return ret;
}



int get_hardware_id(char* hardware_id)
{
	unsigned char data[20] = {0};
	unsigned char md5sum[16];
	unsigned char raw_mac_addr[6];
	unsigned char tmp_data[4]={'\0'};
	char tmp[3]={'\0'};
	char buf[33]={'\0'};
	int i;
	MD5_CTX ctx;

	if(NULL == hardware_id) {
		return 1;
	}
	hardware_id[0] = '\0';
	/* Get mac address */
	if( 0 == get_mac(raw_mac_addr)){
		for(i=0; i<6; i++){
			sprintf(tmp_data,"%2.2x:",raw_mac_addr[i]);
			strcat(data,tmp_data);
		}
	} else {
		strcpy(data, "00:00:00:00:00:00");
	}
	data[17]='\0';

	printf("macaddr  : %s\n", data);
	/*
	 * Then do something else
	 * MD5(data,strlen(data),md5sum);
	 */
	MD5_Init(&ctx);
	MD5_Update(&ctx,data,strlen(data));
	MD5_Final(md5sum,&ctx);

	for (i = 0; i < 4; i++)
	{
		sprintf(tmp,"%2.2X",md5sum[i]);
		strcat(hardware_id, tmp);
	}

	return 0;
}


#define __TEST___

#ifdef __TEST___
int main(int argc, char* argv[])
{
	int ret = 0;

	char str[20];

	while(1) {
		ret = get_hardware_id(str);
		if( 0 == ret) {
			printf("hashvalue: %s\n", str);
		} else {
			printf("hashvalue: %s\n", str);
		}
		break;
	}
	return ret;
}
#endif


