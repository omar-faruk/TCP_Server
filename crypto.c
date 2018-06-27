//
// Created by munna on 6/26/18.
//

#include "crypto.h"

void encodeData(uint8_t *msg, uint8_t *enc_data, int raw_data_len, int *enc_len){

    int i,j;
    uint8_t ms_bits,value;
    bool a;

    if(raw_data_len%7 != 0){
        while(raw_data_len%7!=0){
            msg[raw_data_len] = 0x00;
            raw_data_len++;
        }
    }

    for(i=0,j=0;i<raw_data_len;i++){

        ms_bits = ms_bits | (((_Bool)(msg[i]&(1<<7)))<<(6-(i%7)));
        printf("%x ",ms_bits);
        enc_data[j++]=(msg[i]&~(1<<7));

        if(((i+1)%7)==0 && i>0){
            enc_data[j++]=(ms_bits);
            printf("encoded ms_bits: %x\n",ms_bits);
            ms_bits = 0x00;
        }
    }
    enc_data[j]='\0';
    *enc_len=j;


}

void decodeData(uint8_t *encoded_data, uint8_t *decoded_data, int len,int *decoded_data_length){

    int i,j;
    uint8_t ms_bits=0;
    for(i=0,j=0;i<len;i++){

        if((i+1)%8==0){
            ms_bits=(uint8_t)(encoded_data[i+8]);
            continue;
        }
        if(i==0){
            ms_bits=(uint8_t)(encoded_data[7]);
        }
        decoded_data[j++]=encoded_data[i]|((bool)(ms_bits&(1<<(6-(i%8))))<<7);
    }
    *decoded_data_length=j;
    decoded_data[j]='\0';
}

void printData(uint8_t *msg, int msg_len){
    int i;
    for(i=0;i<msg_len;i++)
    {
        printf("%x ",msg[i]);
    }
    puts("");
}