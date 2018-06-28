//
// Created by munna on 6/27/18.
//

#include "lookup.h"

uint8_t * lookup(int socket_fd, int command_value){

    int i,table_idx=-1;

    for(i=0; i< table_size; i++){

        if(cmd_lookup_table[i].socket_fd == socket_fd){
            table_idx = i;
            break;
        }
    }

    if(table_idx == -1){
        return "no reply entry found";
    }

    for(i=0;i<cmd_lookup_table[table_idx].total_entries;i++){
        if(cmd_lookup_table[table_idx].entries[i].cmd_value == command_value){
            return cmd_lookup_table[table_idx].entries[i].msg;
        }
    }
}

int insert(uint8_t *msg, uint8_t cmd_value, int socket_fd){

    int table_entry_idx=0,i;
    bool new_entry = true;

    for(i=0;i<table_size;i++){

        if(cmd_lookup_table[i].socket_fd == socket_fd){
            table_entry_idx = i;
            new_entry = false;
            break;
        }
    }

    if(new_entry){
        table_entry_idx = socket_fd / 2;
        table_size++;
    }

    cmd_lookup_table[table_entry_idx].socket_fd = socket_fd;
    cmd_lookup_table[table_entry_idx].entries->msg = msg;
    cmd_lookup_table[table_entry_idx].entries->cmd_value = cmd_value;

    return table_entry_idx;
}