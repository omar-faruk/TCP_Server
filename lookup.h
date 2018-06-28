//
// Created by munna on 6/27/18.
//

#ifndef VTSTESTSERVER_LOOKUP_H
#define VTSTESTSERVER_LOOKUP_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct reply{
    uint8_t *msg;
    uint8_t cmd_value;
}Entry;

typedef struct lookup_table{
    Entry *entries;
    int socket_fd;
    int total_entries;
}Ltable;

Ltable *cmd_lookup_table;
int table_size;


uint8_t* lookup(int socket_fd, int command_value);

int insert(uint8_t *msg, uint8_t cmd_value, int socket_fd);

#endif //VTSTESTSERVER_LOOKUP_H
