// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include "channel.h"
#include "crypto.h"

#define PORT 6842

pthread_t listener_thread;

typedef enum{
    CONTROL= 0,
    GPS,
    ENGINE,
    AC,
    DOOR,
    PANIC,
    GEOFENCE,
    AUDIOSPY,
    IMAGE,
    FUEL,
    LOUDHORN,
    BATTERY
}ChannelID;

int msglen(uint8_t *msg)
{
    int length=1;

    while(msg[length++]!=0x79){}

    return length;
}

void parser(uint8_t *msg, int msg_len,int socket_fd){

    int i;

    if(msg[0]!= 0xF9){
        perror("invalid packet");
    }
    else{

        switch (msg[1])
        {
            case CONTROL:
                puts("open controll channel");
                control(msg,msg_len,socket_fd);
                break;

            case GPS:
                puts("open GPS channel");
                break;

            case ENGINE:
                puts("open ENGINE channel");
                break;

            case AC:
                puts("open AC chanel");
                break;

            case DOOR:
                puts("open DOOR channel");
                break;

            case PANIC:
                puts("open PANIC channel");
                break;

            case GEOFENCE:
                puts("open GEOFENCE channel");
                break;

            case AUDIOSPY:
                puts("open AUDOPSPY channel");
                break;

            case IMAGE:
                puts("open IMAGE channel");
                break;

            case FUEL:
                puts("open FUEL channel");
                break;

            case LOUDHORN:
                puts("open LOUDHORN channel");
                break;

            case BATTERY:
                puts("open BATTERY channel");
                break;

            default:
                puts("unknown channel id");
                break;
        }
    }
}

void *read_socket(void *sock_ptr) {
    uint8_t buffer[1024];
    uint8_t data[1024];
    int i,data_length = 0;
    int socket_fd = *((int *)sock_ptr);
    free(sock_ptr);

    printf("Communication socket: %d\n",socket_fd);

    while(1)
    {
        read(socket_fd,buffer,1024);

        if(strlen(buffer)>0)
        {
            printf("bytes received: %d\n",msglen(buffer));
            printData(buffer,msglen(buffer));
            decodeData(buffer,data,msglen(buffer),&data_length);
            parser(data,data_length,socket_fd);
        }

        //printf("Input for socket:%d\t:",socket_fd);
        //scanf("%s",buffer);
        //send(socket_fd,buffer,strlen(buffer),0);

        memset(buffer,0,1024);
        memset(data,0,1024);
    }

}

void *listener() {

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
        puts("bind successfull");
        if (listen(server_fd, 3) < 0)
        {
            perror("listen");
            exit(EXIT_FAILURE);
        }
        puts("listen successfull");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        puts("accept successfull");
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
        puts("");
    }


}

int main(int argc, char const *argv[]) {

    int status;

    status = pthread_create(&listener_thread, NULL, listener, NULL);


    if(status != 0 ){
        puts("cannot start listener thread\n");
    }

    while(1)
    {
        sleep(1000);
    }

}
