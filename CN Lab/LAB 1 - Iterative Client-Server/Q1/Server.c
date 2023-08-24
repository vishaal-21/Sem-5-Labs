#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define PORTNO 9999
void main(){
    int newsockfd,portno,clilen,n;
    struct sockaddr_in seraddr,cliaddr;
    char buffer[256];

    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    seraddr.sin_family=AF_INET;
    seraddr.sin_addr.s_addr=inet_addr("10.86.5.137");
    seraddr.sin_port=htons(PORTNO);

    bind(sockfd,(struct sockaddr*) &seraddr,sizeof(seraddr));

    listen(sockfd,5);

    while(1){
        printf("\nServer waiting...");

        clilen=sizeof(seraddr);

        newsockfd=accept(sockfd,(struct sockaddr*) &seraddr,(socklen_t*)&clilen);

        n=read(newsockfd,buffer,sizeof(buffer));
        printf("\nMessage from client : %s",buffer);

        for(int i=0;buffer[i]!='\0';i++)
            buffer[i]-=4;
        printf("\nDecrypted Message: %s",buffer);
    }
}
