//
// Created by munna on 6/26/18.
//

#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdint.h>
#include <sys/socket.h>
#include "crypto.h"
#include "lookup.h"
#include "datatypes.h"

void control(uint8_t *msg, int msg_len,Connection *conn_ptr);
void gps(uint8_t *msg, int msg_len,Connection *conn_ptr);
void loudhorn(uint8_t *msg, int msg_len,Connection *conn_ptr);
void engine(uint8_t *msg, int msg_len,Connection *conn_ptr);
void battery(uint8_t *msg, int msg_len,Connection *conn_ptr);
void ac(uint8_t *msg, int msg_len,Connection *conn_ptr);
void door(uint8_t *msg, int msg_len,Connection *conn_ptr);
void panic(uint8_t *msg, int msg_len,Connection *conn_ptr);

#endif //CHANNEL_H
