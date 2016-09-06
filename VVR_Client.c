#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "VVRFileTransfer.h"


void error(const char *msg)
{
    perror(msg);
    exit(0);
}
void packForm(struct vvr_packet *packet, size_t bytes_read, uint8_t flag){
    
    
     bytes_read= fread(packet->payload, 500, 1, fp);  
    printf("bytes read %d",bytes_read);
     packet->seq_no =  seqNo;
     packet->ack_no = last_pkt_ack;
     packet->flag = flag;
     packet->length = 500;
 
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n,fromlen,fromlen2;
    struct sockaddr_in serv_addr,from;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &from, sizeof(from));
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    fromlen = sizeof(struct sockaddr_in);
    printf("checkpint 1");
    //Opening the file to split it
     fp= fopen("test.txt", "r+");
     fseek(fp,0, SEEK_END);
     long int size = ftell(fp);
     fseek(fp, 0, SEEK_SET);
     size_t bytes_read;
     
     seqNo += 1;
     
    //call forming packet function
      vvr_packet *packet = (vvr_packet *)malloc (sizeof(vvr_packet) + 500);
      if (packet ==NULL)
        printf("could not malloc");
       else
        printf("malloc success");
      uint8_t vvr_flag =0;
      packForm (packet, bytes_read , vvr_flag);
     uint32_t sizeofpacket = sizeof(vvr_packet) + 500;
     

    n = sendto(sockfd,packet,sizeofpacket,0,(struct sockaddr *) &serv_addr,fromlen);
     if (n < 0)
     error("sendto");
    bzero(buffer,256);
    close(sockfd);
    free(packet);
    fclose(fp);
    return 0;
}
