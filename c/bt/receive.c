// read some bytes from a charater device 

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h> // malloc
#include <stdio.h>
#include <string.h>


static const char* DEFAULT_DEVICE = "/dev/rfcomm0";

int main(int argc, char* argv[])
{
    int fd = -1;
    char* buf = 0;
    int bufsize = 4096;
    int byte_count;
    const char* device;

    if (argc < 2) {
        device = DEFAULT_DEVICE;
    } else {
        device = argv[1]; // blindly accept the first cmd line arg as a device path
    }

    buf = malloc(bufsize);
    if (!buf) {
        fprintf(stderr, "failed to allocate buffer\n");
        goto DONE;
    }


    fd = open(device, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("open()");
        goto DONE;
    }

    memset(buf, 0, bufsize);
    while ((byte_count=read(fd, buf, bufsize-1)) > 0) {
        puts(buf);
        memset(buf, 0, bufsize);
    }


DONE:
    if (fd > 0) {
        close(fd);
    }

    if (buf) {
        free(buf);
    }

    return 0;
}

