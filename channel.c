//
// Created by munna on 6/26/18.
//

#include <stdio.h>
#include <string.h>
#include "channel.h"


void control(uint8_t *msg, int msg_len, int socket_fd)
{
    int i,payload_length,cr_byte,channel_id;

    uint8_t reply[1024],payload[1024],crc;

    cr_byte = msg[2];


    memset(reply,0,1024);
    memset(payload,0,1024);

    if(cr_byte & 0x81){
        payload_length = msg[3]-1;
        channel_id = msg[4];

        if(payload_length>1){
            printf("payload: ");
            for(i = 5; i<(5+payload_length);i++){
                payload[i-5] = msg[i];
            }
            printData(payload,payload_length);
        }
    }

    crc = msg[i];

    if(cr_byte == 0x88){
        payload_length = msg[3]-1;
        uint8_t *reply_string = (uint8_t *)malloc(payload_length*sizeof(uint8_t));
        int j,command_value = msg[4],lookup_table_id=msg[5];

        for(j=5;j<payload_length+5;j++)
        {
            reply_string[j-5] = msg[j];
        }
        insert(reply_string,command_value,lookup_table_id);
    }

    if(cr_byte != 0x88){
        int lookup_table_id;
        char *tmp = lookup(lookup_table_id,cr_byte);
        strcpy(reply,tmp);
        puts(reply);
        send(socket_fd,reply,strlen(reply),0);
    }

    if(cr_byte == 0x88){
        send(socket_fd,"entry success",13,0);
    }

}