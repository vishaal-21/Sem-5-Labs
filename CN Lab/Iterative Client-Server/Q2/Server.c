#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORTNO 9999

void removeDuplicates(char *sentence) {
    char result[1024] = "";
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        if (strstr(result, token) == NULL) {
            strcat(result, token);
            strcat(result, " ");
        }
        token = strtok(NULL, " ");
    }
    strcpy(sentence, result);
}

void main()
{
    int newsockfd, portno, clilen;
    struct sockaddr_in seraddr, cliaddr;
    char buffer[256];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket error");
        exit(1);
    }
    printf("Server socket created..\n");

    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("10.86.5.137");
    seraddr.sin_port = htons(PORTNO);

    if (bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr)) < 0)
    {
        perror("Bind error");
        exit(1);
    }
    printf("Socket bind successful...\n");

    if (listen(sockfd, 5) == 0)
        printf("Listening..\n");
    else
    {
        printf("Listening failed...");
        exit(1);
    }

    clilen = sizeof(seraddr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);

    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        read(newsockfd, buffer, sizeof(buffer));
        if (strcmp(buffer, "Stop") == 0)
        {
            printf("\nServer terminated...");
            exit(0);
        }
        printf("\nMessage from client : %s", buffer);

        removeDuplicates(buffer);

        write(newsockfd, buffer, sizeof(buffer));
    }

    close(newsockfd);
}
