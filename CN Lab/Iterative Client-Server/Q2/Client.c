#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORTNO 9999
void main()
{
    int len, result, n;
    struct sockaddr_in address;
    char ch[256], buffer[256];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket error");
        exit(1);
    }
    printf("Client socket created..\n");

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("10.86.5.137");
    address.sin_port = htons(PORTNO);
    len = sizeof(address);

    result = connect(sockfd, (struct sockaddr *)&address, len);
    if (result == -1)
    {
        perror("\nConnection error");
        exit(1);
    }
    printf("Connected to the server");

    while (1)
    {
        printf("\nEnter String (\"Stop\" to stop): ");
        gets(ch);
        ch[strlen(ch)] = '\0';

        write(sockfd, ch, strlen(ch));

        if (strcmp(ch, "Stop") == 0)
        {
            printf("Client terminated...");
            exit(0);
        }
        
        read(sockfd, ch, strlen(ch));
        
        printf("\\nMessage from server : %s", ch);
    }

    close(sockfd);
}
