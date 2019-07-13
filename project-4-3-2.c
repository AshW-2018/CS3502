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
    unsigned char *p_map;

    // open proc file
    // map p_map to the proc file and grant read & write privilege
    // design test case to read from and write to p_map
    // unmap p_map from the proc file
    return 0;
}
