//
// Created by munna on 6/26/18.
//

#include "channel.h"

void control(uint8_t *msg, int msg_len)
{
    int i,payload_length;
    uint8_t *p;

    payload_length = msg[3];
    
}