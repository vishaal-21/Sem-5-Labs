#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#define PORT 9999

void main(){
    int client_socket = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("172.16.59.86");
    address.sin_port=htons(PORT);

    int len=sizeof(address);

    int size;
    int num;

    printf("Enter number of arrays : ");
    scanf("%d",&num);

    printf("\nEnter size of arrays : ");
    scanf("%d",&size);

    int res[num][size];
    int i;

    sendto(client_socket,&num,sizeof(num),0,(struct sockaddr*) &address, len);
    sendto(client_socket,&size,sizeof(size),0,(struct sockaddr*) &address, len);

    for(i=1;i<=num;i++){
        int arr[size];
        printf("Enter %d elements for array %d:\n",size,i);
        for(int i=0;i<size;i++)
            scanf("%d",&arr[i]);

        sendto(client_socket,arr,sizeof(arr),0,(struct sockaddr*) &address, len);
    }

    recvfrom(client_socket,res,sizeof(res),0,(struct sockaddr*) &address, &len);

    for(int i=0;i<num;i++){
        for(int j=0;j<size;j++){
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }
}