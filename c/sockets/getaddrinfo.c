#define _POSIX_SOURCE 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>




int main(int argc, char* argv[])
{
    struct addrinfo hints;
    struct addrinfo* ai = 0;
    struct addrinfo* rp;
    int bufsize = 512;
    char* buf = 0;
    int rc;

    buf = malloc(bufsize);
    if (!buf) {
        fprintf(stderr, "malloc() failed to allocate %d bytes\n", bufsize);
        goto OUT;
    }

    memset(&hints, 0, sizeof hints);
//    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
//    hints.ai_protocol = 0;
//    hints.ai_canonname = NULL;
//    hints.ai_addr = NULL;
//    hints.ai_next = NULL;

    ai = NULL;
    rc = getaddrinfo(argv[1], "80", &hints, &ai);
    if (rc != 0) {
        fprintf(stderr, "getaddrinfo(),  %s\n", gai_strerror(rc));
    }


    for (rp = ai; rp != NULL; rp = rp->ai_next) {
        const char* name = 0;
        int af = rp->ai_family;

        if (rp->ai_canonname) {
            printf("%s:\n", rp->ai_canonname);
        }

        if (af == AF_INET) {
            struct sockaddr_in* sa = (struct sockaddr_in*)rp->ai_addr;
            name = inet_ntop(af, &sa->sin_addr, buf, bufsize);
            printf("\tipv4: %s\n", name);
        } else if (af == AF_INET6) {
            struct sockaddr_in6* sa = (struct sockaddr_in6*)rp->ai_addr;
            name = inet_ntop(af, &sa->sin6_addr, buf, bufsize);
            printf("\tipv6: %s\n", name);
        } else {
            name = 0;
        }
    }

    freeaddrinfo(ai);

OUT:
    if (buf) {
        free(buf);
    }

    printf("done\n");


    return 0;
}
