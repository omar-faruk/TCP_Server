//
// Created by munna on 6/27/18.
//

#ifndef VTSTESTSERVER_LOOKUP_H
#define VTSTESTSERVER_LOOKUP_H

#include <stdint.h>

typedef struct lookup_table{
    uint8_t **msg;
    int no_of_entries;
    int socket_fd;
}LTable;

#endif //VTSTESTSERVER_LOOKUP_H
