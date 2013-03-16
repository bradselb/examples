#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char* argv[])
{
    char* serverip = argv[1];
    int serverport = 1787;

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
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
        goto EXIT;
    }

    // set up a buffer for text to send.
    const int bufsize = 1024;
    char* buf = malloc(bufsize);
    if (!buf) {
        goto EXIT;
    }
    memset(buf, 0, bufsize);

    while (fgets(buf, bufsize, stdin)) {
        // strip off the end of line char, if any.
        char* p = strpbrk(buf, "\n\r");
        if (p) *p = 0;

        // be honest about length of message to send.
        int len = strnlen(buf, bufsize);

        int txbytes = sendto(sock, buf, len, 0, (struct sockaddr*)&serveraddr, serveraddrlen);

        printf("sent %d bytes to '%s:%d'. message is: '%s'\n", txbytes, serverip, serverport, buf);

        if (0 == strncmp(buf, "quit", 4))  break;
    }

EXIT:

    if (buf) {
        free(buf);
    }
    return 0;
}

