#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char* argv[])
{
    // for each file named on the command line
    // open the file, read four characters and print them to stdout, close the file
    int fd;
    char buf[8];
    const int bufsize = sizeof buf;
    char* filename;

    for (int i = 1; i < argc; ++i) {
        filename = argv[i];
        fd = open(filename, O_RDONLY);
        if (fd > 0) {
            memset(buf, 0, bufsize);
            read(fd, buf, bufsize);
            close(fd);
            printf("%s : '", filename);
            for (int j=0; j<bufsize; ++j) {
                if (isprint(buf[j])) {
                    putchar(buf[j]);
                } else {
                    break;
                }
            }
            puts("'\n");
        }
    }

    return 0;
}
