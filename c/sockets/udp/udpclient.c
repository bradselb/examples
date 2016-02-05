#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// usage: udpclient <server ip address> [<server port number>]
// reads lines from stdin and sends each line to the server 
// in a separate message. It expects a reply from the server.
// 
// TODO: use getaddrinfo() to lookup server ip in DNS
// TODO: use poll or select to implement a timeout on the reply.

int main(int argc, char* argv[])
{
    char* serverip = argv[1];
    int serverport = 1787;
    char* buf = 0;
    const int bufsize = 1024;
    int sock = -1;

    buf = malloc(bufsize);
    if (!buf) {
        goto EXIT;
    }
    memset(buf, 0, bufsize);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { 
        perror("socket()");
        goto EXIT;
    } 

    // set up address of server.
    struct sockaddr_in serveraddr;
    int serveraddrlen = sizeof serveraddr;

    if (2 < argc) {
        serverport = atoi(argv[2]);
    }

    memset(&serveraddr, 0, serveraddrlen);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(serverport);
    int rc = inet_pton(AF_INET, serverip, &serveraddr.sin_addr);
    if (rc != 1) {
        // not successful.
        fprintf(stderr, "(%s:%d) inet_pton() returned: %d\n", __FILE__,__LINE__, rc);
        goto EXIT;
    }


    while (fgets(buf, bufsize, stdin)) {
        // strip off the end of line char, if any.
        char* p = strpbrk(buf, "\n\r");
        if (p) *p = 0;

        printf("sending: '%s'\n", buf);
        fflush(stdout);

        int len = strnlen(buf, bufsize);
        int txbytes = sendto(sock, buf, len, 0, (struct sockaddr*)&serveraddr, serveraddrlen);
        printf("sent %d bytes to '%s:%d'. message is: '%s'\n", txbytes, serverip, serverport, buf);

        memset(buf, 0, bufsize);
        read(sock, buf, bufsize);
        printf("%s\n", buf);
    }

EXIT:
    if (sock > 0) {
        close(sock);
    }

    if (buf) {
        free(buf);
    }
    return 0;
}

