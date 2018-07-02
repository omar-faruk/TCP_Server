//
// Created by munna on 6/27/18.
//

#include "lookup.h"

uint8_t* lookup(uint8_t lookup_table_id, uint8_t command_value){

    int i,table_idx=-1;

    printf("searching for entry with lookup table id: %x, cmd_value: %x\n",lookup_table_id,command_value);

    for(i=0; i< table_size; i++){
        if(cmd_lookup_table[i].lookup_table_id == lookup_table_id){
            //printf("lookup table id: %x\n",cmd_lookup_table[i].lookup_table_id);
            table_idx = i;
            break;
        }
    }

    if(table_idx == -1){
        return "no reply entry found";
    }


    for(i=0;i<cmd_lookup_table[table_idx].total_entries;i++){
        //printf("command value %x\n",cmd_lookup_table[table_idx].entries[i].cmd_value);
        if(cmd_lookup_table[table_idx].entries[i].cmd_value == command_value){
            //printf("found reply %s",cmd_lookup_table[table_idx].entries[i].msg);
            return cmd_lookup_table[table_idx].entries[i].msg;
        }
    }
}

int insert(uint8_t *msg, uint8_t cmd_value, uint8_t lookup_table_id){

    int table_entry_idx=0,i;
    bool new_entry = true;

    //printf("current table size: %d\n",table_size);
    //puts("look up...");
    //printf("inserting new reply %s to cmd value: %x for lookup table id %d\n",msg,cmd_value,table_entry_idx);
    for(i=0;i<table_size;i++){

        if(table_size < 1) break;

        if(cmd_lookup_table[i].lookup_table_id == lookup_table_id){
            table_entry_idx = i;
            new_entry = false;
            break;
        }
    }
    if(new_entry){
        //puts("no entry found, entry to lookup table");
        table_entry_idx = table_size;
        table_size++;
    }

    //printf("index of table entry: %d\n",table_entry_idx);
    //printf("inserting new reply %s to cmd value: %x for lookup table id %d\n",msg,cmd_value,table_entry_idx);

    cmd_lookup_table[table_entry_idx].lookup_table_id = lookup_table_id;
    cmd_lookup_table[table_entry_idx].entries = (Entry *)(malloc(sizeof(Entry)));

    cmd_lookup_table[table_entry_idx].entries->msg = msg;
    cmd_lookup_table[table_entry_idx].entries->cmd_value = cmd_value;
    cmd_lookup_table[table_entry_idx].total_entries++;
    printf("entry successfull %s, cmd value: %x \n",cmd_lookup_table[table_entry_idx].entries->msg,cmd_lookup_table[table_entry_idx].entries->cmd_value);

    return table_entry_idx;
}

int add_new_device(uint8_t *vts_id)
{
    devices[no_of_devices].id = no_of_devices;
    devices[no_of_devices].vts = vts_id;

    //printf("%s \n",devices[no_of_devices].vts);
    //printf("new device: %s added to table id: %d\n",devices[no_of_devices].vts,no_of_devices);

    return  no_of_devices++;;
}

int vts_entry_id(uint8_t *vts_id)
{
    int i;

    for(i = 0; i < no_of_devices; i++){
        if(strcmp(devices[i].vts,vts_id)==0){
            return devices[i].id;
        }
    }
    return -1;
}