#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
   int quit = 0;
   int port = 1787;
   int sock = 0;
   struct sockaddr_in myaddr;
//   struct ip_mreq groupaddr;

   const int bufsize = 1024;
   char* buffer = malloc(bufsize);
   if (!buffer) {
      goto EXIT;
   }

   if (1 < argc) {
      // assume first arg is port number
      port = atoi(argv[1]);
   }

   memset(&myaddr, 0 , sizeof myaddr);
   myaddr.sin_family = AF_INET;
   myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   myaddr.sin_port = htons(port);

   //memset(&groupaddr, 0, sizeof groupaddr);
   //groupaddr.imr_interface.s_addr = myaddr.sin_addr.s_addr;
   //inet_pton(AF_INET, "224.0.1.1", &groupaddr.imr_multiaddr.s_addr); // returns 1 if OK


   sock = socket(AF_INET, SOCK_DGRAM, 0);
   if ( sock < 0 ) { 
      perror("socket()");
      goto EXIT;
   }
   if ( 0 != bind(sock, (struct sockaddr*)&myaddr, sizeof myaddr) ) {
      perror("bind()");
      goto EXIT;
   }
   //if (0 != setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &groupaddr, sizeof groupaddr)) {
   //   perror("setsockopt()");
   //   goto EXIT;
   //}

   while (!quit) {
      struct sockaddr_in clientaddr;
      socklen_t clientaddrlen = sizeof clientaddr;
      char* clientip = 0;
      int clientport = 0; 
      int rxbytes = 0;

      memset(buffer, 0, bufsize);
      memset(&clientaddr, 0, clientaddrlen);
      rxbytes = recvfrom(sock, buffer, bufsize, 0, (struct sockaddr*)&clientaddr, &clientaddrlen);

      // for now, simply print out the received message.
      clientip = inet_ntoa(clientaddr.sin_addr);
      clientport = ntohs(clientaddr.sin_port);
      fprintf(stdout, "received %d bytes from '%s:%d'. message is: '%s'\n", rxbytes, clientip, clientport, buffer);
      fflush(stdout);

      if ( 0 == strncmp(buffer, "quit", 4) ) {
         quit = 1;
      }

      // say ok.
      int len = snprintf(buffer, bufsize, "Ok.");
      sendto(sock, buffer, len, 0, (struct sockaddr*)&clientaddr, clientaddrlen);
   }

EXIT:
   if (sock > 0) {
      close(sock);
   }
   if (buffer) {
      free(buffer);
   }

   return 0;
}

