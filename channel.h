//
// Created by munna on 6/26/18.
//

#ifndef VTSTESTSERVER_CHANNEL_H
#define VTSTESTSERVER_CHANNEL_H

#include <stdint.h>

void control(uint8_t *msg, int msg_len);
void gps(uint8_t *msg, int msg_len);
void loudhorn(uint8_t *msg, int msg_len);
void engine(uint8_t *msg, int msg_len);
void battery(uint8_t *msg, int msg_len);
void ac(uint8_t *msg, int msg_len);
void door(uint8_t *msg, int msg_len);
void panic(uint8_t *msg, int msg_len);

#endif //VTSTESTSERVER_CHANNEL_H
