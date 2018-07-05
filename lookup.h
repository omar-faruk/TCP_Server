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

#include "datatypes.h"

Ltable *cmd_lookup_table;
VTS *devices;

int no_of_devices;
int table_size;


uint8_t* lookup(uint8_t lookup_table_id, uint8_t command_value);
int insert(uint8_t *msg, uint8_t cmd_value, uint8_t lookup_table_id);
int add_new_device(uint8_t *device_id);
int vts_entry_id(uint8_t *device_id);

#endif //VTSTESTSERVER_LOOKUP_H
