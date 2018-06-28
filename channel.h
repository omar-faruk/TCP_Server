//
// Created by munna on 6/26/18.
//

#ifndef VTSTESTSERVER_CHANNEL_H
#define VTSTESTSERVER_CHANNEL_H

#include <stdint.h>
#include <sys/socket.h>
#include "crypto.h"
#include "lookup.h"

void control(uint8_t *msg, int msg_len,int socket_fd);
void gps(uint8_t *msg, int msg_len,int socket_fd);
void loudhorn(uint8_t *msg, int msg_len,int socket_fd);
void engine(uint8_t *msg, int msg_len,int socket_fd);
void battery(uint8_t *msg, int msg_len,int socket_fd);
void ac(uint8_t *msg, int msg_len,int socket_fd);
void door(uint8_t *msg, int msg_len,int socket_fd);
void panic(uint8_t *msg, int msg_len,int socket_fd);

#endif //VTSTESTSERVER_CHANNEL_H
