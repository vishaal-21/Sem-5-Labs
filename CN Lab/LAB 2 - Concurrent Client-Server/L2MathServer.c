#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define PORTNO 9999

float calc(float a, float b, char ch){
    switch(ch){
        case '+':
        return a+b;
        break;

        case '-':
        return a-b;
        break;

        case '*':
        return a*b;
        break;

        case '/':
        return a/b;
        break;
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
    float a,b;
    char ch;

    while(1){
        newsocket=accept(sockfd,(struct sockaddr*) &client,&clilen);
        
        if(fork()==0){
            recv(newsocket,&a,sizeof(a),0);
            recv(newsocket,&b,sizeof(b),0);
            recv(newsocket,&ch,sizeof(ch),0);

            float res = calc(a,b,ch);
            send(newsocket,&res,sizeof(res),0);
            close(newsocket);
        }
    }

    close(sockfd);
}