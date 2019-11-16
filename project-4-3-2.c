#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#define PAGE_SIZE 4096

int main(int argc , char *argv[])
{
        int fd;
        int i;
        unsigned char *p_map;

        /* open proc file */
        fd = open("/proc/mydir/myinfo", O_RDWR);
        if(fd < 0) {
                printf("open fail\n");
                exit(1);
        }else {
                printf("open successfully\n");
        }

    // map p_map to the proc file and grant read & write privilege
    // read data from p_map
    // unmap p_map from the proc file

    return 0;
}
