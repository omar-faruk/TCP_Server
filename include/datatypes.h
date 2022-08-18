//
// Created by munna on 7/5/18.
//

#ifndef DATATYPE_H
#define DATATYPE_H

typedef struct reply{
    uint8_t *msg;
    uint8_t cmd_value;
}Entry;

typedef struct lookup_table{
    Entry *entries;
    uint8_t lookup_table_id;
    int total_entries;
}Ltable;

typedef struct vts_id{
    uint8_t *vts;
    int id;
}VTS;

typedef struct _connection{
    int socket_fd;
    uint8_t *vts_id;
    int vts_entry_id;
}Connection;

#endif //DATATYPE_H
