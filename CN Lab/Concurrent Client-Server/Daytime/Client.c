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
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORTNO);

    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("\nConnection error");
        exit(1);
    }
    printf("Connection successful\n");

    char buffer[1024];
    recv(sockfd,buffer,sizeof(buffer),0);
    printf("%s",buffer);

    close(sockfd);
}
