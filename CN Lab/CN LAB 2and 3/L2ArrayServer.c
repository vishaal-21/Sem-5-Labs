#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define PORTNO 9999

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

void main(){
    int newsocket;
    struct sockaddr_in server,client;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket not created");
        exit(1);
    }
    printf("Server Socket creation successful...\n");

    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("172.16.59.86");
    server.sin_port=htons(PORTNO);

    if(bind(sockfd,(struct sockaddr*) &server,sizeof(server))<0){
        perror("Binding error");
        exit(1);
    }
    printf("Bind successful..\n");

    if(listen(sockfd,5)<0){
        perror("Listening error");
        exit(1);
    }
    printf("Listening...\n\n");

    int clilen=sizeof(client);

    while(1){
        newsocket=accept(sockfd,(struct sockaddr*) &client,&clilen);
        
        if(fork()==0){
            int size;
            recv(newsocket,&size,sizeof(size),0);

            int numbers[size];
            recv(newsocket,numbers,sizeof(numbers),0);

            bubbleSort(numbers,size);
            int id=getpid();
            
            send(newsocket,&id,sizeof(id),0);
            send(newsocket,numbers,sizeof(numbers),0);

            close(newsocket);
        }
    }

    close(sockfd);
}