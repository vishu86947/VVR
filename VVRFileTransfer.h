//Header file with data strucutre 
/*Flag Parameters:
   0 - Data packet from client
   1 - Data packet from server
   2 - ACK Packet
   3 - NACK Packet
*/

include <stdint.h>
#ifndef SEND_STATIC_WIND_SIZE
#define SEND_STATIC_WIND_SIZE 20
#endif 
#ifndef RECV_STATIC_WIND_SIZE
#define RECV_STATIC_WIND_SIZE 20
#endif 
#ifndef
#define PACKET_LENGTH 500
#endif 

FILE *fp=NULL;
char buffer[256];
char filename[40];
size_t filesize;

//Socket stuff
struct sockaddr_in serv_addr;
struct hostent *server;


uint32_t seqNo =0;
uint32_t last_pkt_ack ;
uint32_t last_pkt_sent;
unsigned char buffer_window[RECV_STATIC_WIND_SIZE][PACKET_LENGTH];

typedef struct vvr_tcb {
    uint32_t send_window_size;
    uint32_t recv_window_size;
    uint8_t  cntrl_options;
}vvr_tcb;

#pragma pack(1)
typedef struct vvr_packet {
    uint32_t seq_no;
    uint32_t ack_no;
    uint8_t flag;   
    uint32_t length;
    //vvr_tcb  TCP;
    //unsigned int CRC : 16;	
    unsigned char payload[1];
}vvr_packet;
#pragma pack(0)