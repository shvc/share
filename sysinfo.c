#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <linux/sysinfo.h>
/*
  struct sysinfo {
                 long uptime;          
               unsigned long loads[3]; 
               unsigned long totalram;
               unsigned long freeram;   
               unsigned long sharedram; 
               unsigned long bufferram; 
               unsigned long totalswap; 
               unsigned long freeswap;  
               unsigned short procs;
               unsigned long totalhigh; 
               unsigned long freehigh;  
               unsigned int mem_unit;   
               char _f[20-2*sizeof(long)-sizeof(int)];
           };
*/
/*
 Returns information on overall system statistics.  
extern int sysinfo (struct sysinfo *__info)

 Return number of configured processors.
extern int get_nprocs_conf (void)

 Return number of available processors.
extern int get_nprocs (void)


 Return number of physical pages of memory in the system.
extern long int get_phys_pages (void)

 Return number of available physical pages of memory in the system.
extern long int get_avphys_pages (void)

*/


void print_sysinfo(struct sysinfo *info)
{
	assert(info);

	printf("uptime    : %ld\n", info->uptime);
	printf("loads 1   : %lu\n", info->loads[0]);
	printf("loads 5   : %lu\n", info->loads[1]);
	printf("loads 15  : %lu\n", info->loads[2]);
	printf("free ram  : %lu\n", info->freeram);
	printf("shared ram: %lu\n", info->sharedram);
	printf("buffer ram: %lu\n", info->bufferram);
	printf("total swap: %lu\n", info->totalswap);
	printf("free swap : %lu\n", info->freeswap);
	printf("procs     : %d\n", info->procs);
	printf("total high: %lu\n", info->totalhigh);
	printf("free high : %lu\n", info->freehigh);
	printf("mem unit  : %lu\n", info->mem_unit);
	printf("%s\n", info->_f);
}

int main(int argc, char** argv)
{
	int rv = 0;

	struct sysinfo info;

	rv = sysinfo(&info);
	if(rv != 0) {
		perror("sysinfo");
	}

	print_sysinfo(&info);

	return rv;
}
