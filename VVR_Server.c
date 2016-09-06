/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "VVRFileTransfer.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;int fromlen;
     
     socklen_t clilen;
     
     struct sockaddr_in serv_addr, cli_addr, from;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_DGRAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
    bzero((char *) &from, sizeof(from));
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
     bzero(buffer,256);
     fromlen = sizeof(struct sockaddr_in);
     
    vvr_packet *packet ;
     //while (1)
     //{
     n = recvfrom(sockfd,packet,500,0,(struct sockaddr *)&from,&fromlen);
     
     if (n < 0) error("recvfrom");
     printf("%s\n",n);
  
     //n = sendto(sockfd,"Got yourmessage",17,0,(struct sockaddr *) &from,fromlen);
     //if (n < 0)
     //error("sendto");
    //}*/
         close(sockfd);

     return 0; 
 }

 
