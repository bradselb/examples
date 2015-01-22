// gcc -Wall -O2 -std=c99 -o map_pci_iomem -I../../projects/lib/ map_pci_iomem.c ../../projects/lib/hexdump.c 

#include "hexdump.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

// intel HD audio controller on the intel DH77EB motherboard.
const char* path = "/sys/bus/pci/devices/0000:00:1b.0/resource0";

int main(int argc, char* argv[])
{
    int fd = 0;
    unsigned char* pmem = 0;
    size_t length = 16384; 

    fd = open(path, O_RDWR);
    if (fd < 0) {
        perror(path);
        goto exit;
    }

    pmem = mmap(0, length, PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);
    if (!pmem) {
        perror("");
        goto exit;
    }

    // success! 
    hexdump(pmem, 0x100);
    fputc('\n', stdout);

exit:
    if (pmem) {
        munmap(pmem, length);
    }

    if (fd > 0) {
        close(fd);
    }

    return 0;
}
