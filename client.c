// Client code

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include "VVRFileTransfer.h"


#define PACKSIZE 500
int nack_flag=0;
char *nackArr = NULL;

// TCP socket connection on 3001,argv for filename

    
    
void send_file(){
    
    int sockfd, portno, n;
    
    char buffer[256];
    
    portno = 3001;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    //bzero(buffer,256);
    //fgets(buffer,255,stdin);
    
    //copy the name of the file to buffer
    //strcpy(buffer,filename);
    
    n = write(sockfd,filename,strlen(filename));
    if (n < 0) 
         error("ERROR writing to socket");
    //bzero(buffer,256);
    n = read(sockfd,&filesize,sizeof(size_t));
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%d\n",filesize);
    close(sockfd);
}

/*  NACK Thread function:
    Create UDP socket on 3002
    check NACK number in nackArr and send to ohter side 
*/
void nack_thr(){
    
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    while(nack_flag !=1){
    
    
        portno = 3002;
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) 
            error("ERROR opening socket");
        server = gethostbyname(argv[1]);
        if (server == NULL) {
            fprintf(stderr,"ERROR, no such host\n");
            exit(0);
        }
        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, 
             (char *)&serv_addr.sin_addr.s_addr,
             server->h_length);
        serv_addr.sin_port = htons(portno);
        if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
            error("ERROR connecting");
        printf("Please enter the message: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0) 
             error("ERROR writing to socket");
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        if (n < 0) 
             error("ERROR reading from socket");
        printf("%s\n",buffer);
        close(sockfd);
        return 0;    
    }
}




/* calc number of packets, malloc global array for tracking
   global nackArr[filesize/pktsize] update with mutex
   global nack_flag for setting when all packets recvd
*/
void calc_pkt(size_t filesize){
    int numPkt = (int)filesize/PACKSIZE + ((filesize%PACKSIZE !=0)? 1:0);
    
}


int main(int argc, char *argv[])
{    
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    memcpy (filename, argv[1],40);
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    send_file();
    
    //Create thread to send NACK packets
    //pthread_t thr1;
    //pthread_create(&thr1,NULL,nack_thr, NULL)

/*  Recv file in main
    Create UDP socket in 3003
    
    whie(1){
        mmap (file);
        recv packet with seqno
    }*/
    return 0;
    
}