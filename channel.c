//
// Created by munna on 6/26/18.
//

#include <stdio.h>
#include <string.h>
#include "channel.h"
#include "crypto.h"

void control(uint8_t *msg, int msg_len, int socket_fd)
{
    int i,payload_length,cr_byte,channel_id;

    uint8_t reply[1024],payload[1024],crc;

    cr_byte = msg[2];
    payload_length = msg[3]-1;

    memset(reply,0,1024);
    memset(payload,0,1024);

    if(cr_byte & 0x80){
        channel_id = msg[4];
    }

    if(payload_length>1){
        printf("payload: ");
        for(i = 5; i<(5+payload_length);i++){
            payload[i-5] = msg[i];
        }
        printData(payload,payload_length);
    }
    crc = msg[i];

}