#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define PORTNO 9999

void main()
{
    int new_server_socket;
    struct sockaddr_in server, client;

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("Socket Error");
        exit(1);
    }
    printf("Socket created\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORTNO);

    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Binding error");
        exit(1);
    }
    printf("Bind successful\n");

    if (listen(server_socket, 5) < 0)
    {
        perror("Listening error");
        exit(1);
    }
    printf("Listening\n");

    int clilen = sizeof(client);
    int pid;

    char response[1024];
    time_t curr_time;
    time(&curr_time);

    while (1)
    {
        new_server_socket = accept(server_socket, (struct sockaddr *)&client, &clilen);

        if (fork() == 0)
        {
                pid=getpid();

                snprintf(response,sizeof(response),"Date and Time : %s\nProcess ID: %d\n",ctime(&curr_time),pid);
                send(new_server_socket,response,sizeof(response),0);
        }

        close(new_server_socket);
    }

    close(server_socket);
}