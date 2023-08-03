#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORTNO 8000
void main(){
    int len,result,n;
    struct sockaddr_in address;
    char ch[256],buffer[256];

    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("172.16.59.28");
    address.sin_port=htons(PORTNO);
    len=sizeof(address);

    result=connect(sockfd,(struct sockaddr*) &address,len);
    if(result==-1){
        perror("\nClient error");
        exit(1);
    }

    printf("\nEnter String : \t");
    gets(ch);

    ch[strlen(ch)]='\0';

    for(int i=0;ch[i]!='\0';i++){
        ch[i]+=4;
    }

    write(sockfd,ch,strlen(ch));
    // printf("String sent back is ..... ");

    // while(1){
    //     n=read(sockfd,buffer,sizeof(buffer));
    //     puts(buffer);
    //     // break;
    // }
}