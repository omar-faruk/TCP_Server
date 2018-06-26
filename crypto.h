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

#endif //VTSTESTSERVER_CRYPTO_H
