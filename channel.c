//
// Created by munna on 6/26/18.
//

#include <stdio.h>
#include <string.h>
#include "channel.h"


void control(uint8_t *msg, int msg_len, Connection *conn_ptr)
{
    int i,payload_length,cr_byte,channel_id,lookup_table_id;
    Connection conn = *conn_ptr;
    uint8_t reply[1024],payload[1024],crc;
    char *tmp;

    cr_byte = msg[2];

    //printf("connected vts id: %s, to socket: %d, lookup table entry id: %d",conn.vts_id,conn.socket_fd,conn.vts_entry_id);

    memset(reply,0,1024);
    memset(payload,0,1024);

    // open channel command
    if(cr_byte == 0x81){
        uint8_t *vts_id;
        payload_length = msg[3]-1;
        channel_id = msg[4];

        if(payload_length>1){
            //printf("payload: ");
            for(i = 5; i<(5+payload_length);i++){
                payload[i-5] = msg[i];
            }
            //printData(payload,payload_length);

            vts_id = (uint8_t *) malloc(payload_length*sizeof(uint8_t));
            vts_id = payload;
            conn.vts_id = vts_id;
        }
        if(vts_entry_id(vts_id)<0){
            conn.vts_entry_id  = add_new_device(vts_id);
            *conn_ptr =conn;
        }
        else{
            conn.vts_entry_id = vts_entry_id(vts_id);
            conn.vts_id = vts_id;
            *conn_ptr = conn;
        }
        lookup_table_id = conn.vts_entry_id;
    }

    else if(cr_byte == 0x88){

        payload_length = msg[3]-1;

        //printf("payload length: %d",payload_length);

        uint8_t *reply_string = (uint8_t *)malloc(payload_length*sizeof(uint8_t));
        int j,command_value = msg[4];

        for(j=6;j<payload_length+6;j++) {
            reply_string[j-6] = msg[j];
        }

        int ret_val = insert(reply_string,command_value,lookup_table_id);

        if(ret_val>=0){
            send(conn.socket_fd,"entry success",13,0);
        }else{
            send(conn.socket_fd,"entry failed",12,0);
        }

    }

    if(cr_byte!=0x88)
    {
        tmp = lookup(lookup_table_id,cr_byte);
        strcpy(reply,tmp);
        puts(reply);
        send(conn.socket_fd,reply,strlen(reply),0);
    }

}