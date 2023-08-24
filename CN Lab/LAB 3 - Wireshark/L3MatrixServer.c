#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 9999

void main(){
    int server_socket = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in server,client;
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("172.16.59.86");
    server.sin_port=htons(PORT);

    bind(server_socket,(struct sockaddr*) &server, sizeof(server));

    int clilen=sizeof(client);

    int num,size,i;

    recvfrom(server_socket,&num,sizeof(num),0,(struct sockaddr*) &server, &clilen);
    recvfrom(server_socket,&size,sizeof(size),0,(struct sockaddr*) &server, &clilen);

    int res[num][size];

    while(1){
        for(i=0;i<num;i++){
            int arr[size];

            memset(arr,0,sizeof(arr));
            
            recvfrom(server_socket,arr,sizeof(arr),0,(struct sockaddr*) &client, &clilen);

            memcpy(res[i],arr,sizeof(arr));
        }

        sendto(server_socket,res,sizeof(res),0,(struct sockaddr*) &client, clilen);
    }
}