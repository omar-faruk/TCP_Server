// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>

#define PORT 6842

pthread_t listener_thread;



void encodeData(uint8_t *msg, uint8_t *enc_data, int raw_data_len, int *enc_len){

    int i,j;
    uint8_t ms_bits,value;
    _Bool a;

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
        decoded_data[j++]=encoded_data[i]|((_Bool)(ms_bits&(1<<(6-(i%8))))<<7);
    }
    *decoded_data_length=j;
    decoded_data[j]='\0';
}

void *read_socket(void *sock_ptr)
{
    uint8_t buffer[1024];
    uint8_t data[1024];
    int i,data_length = 0;
    int socket_fd = *((int *)sock_ptr);
    free(sock_ptr);

    printf("Communication socket: %d\n",socket_fd);

    while(1)
    {
        if(socket_fd)
        read(socket_fd,buffer,1024);

        if(strlen(buffer)>0)
        {
            for(i=0;i<strlen(buffer);i++)
            {
                printf("%x ",buffer[i]);
            }
            puts("");
            decodeData(buffer,data,strlen(buffer),&data_length);
        }

        //printf("Input for socket:%d\t:",socket_fd);
        //scanf("%s",buffer);
        //send(socket_fd,buffer,strlen(buffer),0);

        memset(buffer,0,strlen(buffer));
        memset(data,0,strlen(data));
    }

}

void *listener()
{

	int server_fd, new_socket, valread;
	struct sockaddr_in address;
    struct sockaddr_storage peer_address;
	int opt = 1;
	int addrlen = sizeof(address);


	// Creating socket file descriptor
    while(1){

        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        {
            perror("socket failed");
            exit(EXIT_FAILURE);
        }

        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("192.168.3.21");
        address.sin_port = htons( PORT );

        // Forcefully attaching socket to the port 6842

        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
        {
            perror("bind failed");
            exit(EXIT_FAILURE);
        }
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        int peer_add_len = sizeof(peer_address);

        int ret = getpeername(new_socket, (struct sockaddr *)&peer_address, (socklen_t*)&peer_add_len);


        if(ret < 0){
            printf("%d\n",errno);
        }


        int port;
        char ipstr[20];
        if (peer_address.ss_family == AF_INET) {
            struct sockaddr_in *s = (struct sockaddr_in *)&peer_address;
            port = ntohs(s->sin_port);
            inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
        }

        printf("Peer IP address: %s\n", ipstr);

        pthread_t new_socket_reader;
        //continuously read the socket
        int *socket_arg = malloc(sizeof(*socket_arg));
        *socket_arg = new_socket;
        pthread_create(&new_socket_reader,NULL,read_socket,socket_arg);
    }



}

int main(int argc, char const *argv[])
{

    int status;

    status = pthread_create(&listener_thread, NULL, listener, NULL);


    if(status != 0 ){
        puts("cannot start listener thread\n");
    }

    while(1)
    {

    }

}
