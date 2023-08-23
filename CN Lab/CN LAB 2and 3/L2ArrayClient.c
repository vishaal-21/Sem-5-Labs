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

    int n;
    printf("Enter array size : ");
    scanf("%d",&n);

    int numbers[n],sort[n];

    printf("Enter %d numbers :\n",n);
    for(int i=0;i<n;i++){
        scanf("%d",&numbers[i]);
    }

    send(sockfd,&n,sizeof(n),0);
    send(sockfd,numbers,sizeof(numbers),0);

    int pid;
    recv(sockfd,&pid,sizeof(pid),0);
    recv(sockfd,sort,sizeof(sort),0);

    printf("Sorted array received from server with PID %d:\n", pid);
    for (int i = 0; i < n; i++) {
        printf("%d ", sort[i]);
    }

    close(sockfd);
}