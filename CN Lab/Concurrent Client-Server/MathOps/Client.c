#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORTNO 9999
void main()
{
    struct sockaddr_in address;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket error");
        exit(1);
    }
    printf("Client socket created\n");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("192.168.33.143");
    address.sin_port = htons(PORTNO);

    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("\nConnection error");
        exit(1);
    }
    printf("Connection successful\n");

    float a,b;
    char ch;

    printf("Enter 2 numbers : \n");
    scanf("%f%f",&a,&b);

    printf("Enter an operator : ");
    scanf(" %c",&ch);

    send(sockfd,&a,sizeof(a),0);
    send(sockfd,&b,sizeof(b),0);
    send(sockfd,&ch,sizeof(ch),0);

    float result;
    recv(sockfd,&result,sizeof(result),0);
    printf("Result : %f",result);

    close(sockfd);
}
