//
// Created by munna on 6/26/18.
//

#ifndef VTSTESTSERVER_CRYPTO_H
#define VTSTESTSERVER_CRYPTO_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void encodeData(uint8_t *msg, uint8_t *enc_data, int raw_data_len, int *enc_len);
void decodeData(uint8_t *encoded_data, uint8_t *decoded_data, int len,int *decoded_data_length);
void printData(uint8_t *msg, int msg_len);
int write_to_file(char *filename, char *src, int len);
int hex_file_read(char *filename, uint8_t *dest_array, int *len);
uint8_t str_to_uint_8(char *data);
uint8_t ascii_to_hex(char c);

#endif //VTSTESTSERVER_CRYPTO_H
