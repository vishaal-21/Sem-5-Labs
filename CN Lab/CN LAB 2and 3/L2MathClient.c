#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORTNO 9999
void main(){
    struct sockaddr_in address;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("Socket not created");
        exit(1);
    }
    printf("Client Socket creation successful...\n");

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("172.16.59.86");
    address.sin_port=htons(PORTNO);

    int result=connect(sockfd,(struct sockaddr*) &address,sizeof(address));
    if(result==-1){
        perror("\nClient error");
        exit(1);
    }
    printf("Connection successful...\n");

    float a,b;
    char ch;

    printf("Enter 2 numbers : ");
    scanf("%f%f",&a,&b);

    printf("Enter operator (+,-,*,/) : ");
    scanf(" %c",&ch);

    send(sockfd,&a,sizeof(a),0);
    send(sockfd,&b,sizeof(b),0);
    send(sockfd,&ch,sizeof(ch),0);

    float res;
    recv(sockfd,&res,sizeof(res),0);

    printf("Result = %f",res);


    close(sockfd);
}