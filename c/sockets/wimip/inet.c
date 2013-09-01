
#define _POSIX_SOURCE 1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>




static const char* DefaultHost = "localhost";
static const char* DefaultPort = "62900";


// --------------------------------------------------------------------------
// a bunch of functions that mostly wrap the usual and customary sockets
// stuff. I have taken liberal inspiration from the example code 
// in the most excellent book... 
// Michael Kerrisk, "The Linux Programming Interface", (C) 2010


// --------------------------------------------------------------------------
// a client uses this fctn to establish a connection to a server. 
//
// given a string representation of a host address and port number,
// use dns to lookup the ipv4 address, fill in the socket address structure
// with the host address, open a socket and connect to the server.
// the type argument should be one of SOCK_STREAM or SOCK_DGRAM
// returns:
//    the connected socket fd on success or -1 if not sucessful.
// note: 
//    caller is responsible to close the socket.
int inet_connect(const char* name, const char* port, int type)
{
    int sock;
    struct addrinfo hints;
    struct addrinfo* addrinfo;
    int rc;
 
    sock = -1; // fail by default.

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = type;
    // hints.ai_flags = AI_NUMERICSERV;
    // hints.ai_protocol = 0;
    // hints.ai_canonname = NULL;
    // hints.ai_addr = NULL;
    // hints.ai_next = NULL;

    if (!name) {
        name = DefaultHost;
    }

    if (!port) {
        port = DefaultPort;
    }

    rc = getaddrinfo(name, port, &hints, &addrinfo);
    if (rc != 0) {
        fprintf(stderr, "(%s:%d) %s(), getaddrinfo() returned: %d,  %s\n", __FILE__, __LINE__, __FUNCTION__, rc, gai_strerror(rc));
        goto out;
    }

    struct addrinfo* iter;
    for (iter=addrinfo; iter!=NULL; ++iter) {

        sock = socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
        if (sock < 0) continue;

        rc = connect(sock, iter->ai_addr, iter->ai_addrlen); 
        if (rc < 0) {
            // failed to connect
            fprintf(stderr, "(%s:%d) %s(), connect() returned: %d\n", __FILE__, __LINE__, __FUNCTION__, rc);
            close(sock);
            sock = -1;
        } else {
            // success!
            break;
        }
    }

    freeaddrinfo(addrinfo);

out:
    return sock;
}


// --------------------------------------------------------------------------




// --------------------------------------------------------------------------



// --------------------------------------------------------------------------

