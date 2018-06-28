//
// Created by munna on 6/27/18.
//

#include "lookup.h"

uint8_t * lookup(int socket_fd, int command_value){

    int i,table_idx=-1;

    printf("searching for entry with socket_fd: %d, cmd_value: %d\n",socket_fd,command_value);

    for(i=0; i< table_size; i++){

        printf("socket_fd: %d\n",cmd_lookup_table[i].socket_fd);

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

    printf("current table size: %d\n",table_size);

    printf("inserting new reply %s to cmd value: %x for socket %d\n",msg,cmd_value,socket_fd);

    puts("look up...");

    for(i=0;i<table_size;i++){

        if(table_size < 1) break;

        if(cmd_lookup_table[i].socket_fd == socket_fd){
            table_entry_idx = i;
            new_entry = false;
            break;
        }
    }


    if(new_entry){
        puts("no entry found, entry to lookup table");
        table_entry_idx = table_size;
        table_size++;

    }


    printf("index of table entry: %d\n",table_entry_idx);


    cmd_lookup_table[table_entry_idx].socket_fd = socket_fd;
    cmd_lookup_table[table_entry_idx].entries = (Entry *)(malloc(sizeof(Entry)));

    cmd_lookup_table[table_entry_idx].entries->msg = msg;
    cmd_lookup_table[table_entry_idx].entries->cmd_value = cmd_value;

    puts("entry successfull");

    return table_entry_idx;
}