//Header file with data strucutre 
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


uint32_t last_pkt_ack ;
uint32_t last_pkt_sent;
unsigned char buffer_window[RECV_STATIC_WIND_SIZE][PACKET_LENGTH];

typedef struct vvr_tcb {
uint32_t send_window_size;
uint32_t recv_window_size;
uint8_t  cntrl_options;
    }vvr_tcb;
typedef struct vvr_packet {
uint32_t seq_no;
uint32_t ack_no;
uint8_t flag;
uint32_t lengh;
vvr_tcb  TCP;
    unsigned int CRC : 16;	
unsigned char payload[1];
   }vvr_packet;
