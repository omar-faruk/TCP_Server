#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define PORT 6842

int msglen(uint8_t *msg)
{
	int length=1;

	while(msg[length++]!=0xF9){}

	return length;
}

void printData(uint8_t *msg, int msg_len){
    int i;
    for(i=0;i<msg_len;i++)
    {
        printf("%x ",msg[i]);
    }
    puts("");
}

void encodeData(uint8_t *msg, uint8_t *enc_data, int raw_data_len, int *enc_len){

    int i,j;
    uint8_t ms_bits;
	//_Bool a;

	if(raw_data_len%7 != 0){
		while(raw_data_len%7!=0){
			msg[raw_data_len] = 0xff;
			raw_data_len++;
		}
	}

    for(i=0,j=0;i<raw_data_len;i++){

        ms_bits = ms_bits | (((_Bool)(msg[i]&(1<<7)))<<(6-(i%7)));
        //printf("%x ",ms_bits);
        enc_data[j++]=(msg[i]&~(1<<7));

        if(((i+1)%7)==0 && i>0){
            enc_data[j++]=(ms_bits);
            //printf("encoded ms_bits: %x\n",ms_bits);
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
        decoded_data[j++]=encoded_data[i]|((_Bool)(ms_bits&(1<<(6-(i%8))))<<7);
    }
    *decoded_data_length=j;
    decoded_data[j]='\0';
}

int main(int argc, char const *argv[])
{
    //struct sockaddr_in address;
    int sock = 0,encoded_length;
    struct sockaddr_in serv_addr;
    uint8_t buffer[1024]={0},encoded_msg[1024]={0};


    uint8_t msg[] = {0xF9, 0x00, 0x81, 0x10, 0x01, 0x70, 0x69, 0x68, 0x65, 0x6c, 0x6c,
					 0x6f, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x31, 0x32, 0x33, 0x8A, 0xF9
					};

	//uint8_t msg[] = {0xF9, 0x00, 0x88, 0x0B, 0x05, 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 0x89, 0xF9};

	printf("message length: %d\n",msglen(msg));

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "192.168.3.21", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    while(1){

		printData(msg,msglen(msg));

		encodeData(msg,encoded_msg,msglen(msg),&encoded_length);

		printf("encoded_data_length: %d\nencoded data: ",encoded_length);
		printData(encoded_msg,encoded_length);


		//decodeData(encoded_msg,buffer,encoded_length,&j);

		send(sock , encoded_msg , encoded_length , 0 );

		int valread = read( sock , buffer, 1024);
		printf("received message: %s\n",buffer );
		memset(buffer,0,1024);
		memset(encoded_msg,0,1024);
		//getchar();
		sleep(20);
	}
    return 0;
}

/*
 //test sample
 0xF9, 0x00, 0x81, 0x10, 0x01, 0x70, 0x69, 0x68, 0x65, 0x6c, 0x6c,
 0x6f, 0x77, 0x6f, 0x72, 0x6c, 0x64, 0x31, 0x32, 0x33, 0x8A, 0xF9

 //set reply of a command sample


0xF9, 0x00, 0x88, 0x0B, 0x05, 'h', 'e', 'l', 'l', 'o', 'w', 'o', 'r', 'l', 'd', 0x89, 0xF9

 */
