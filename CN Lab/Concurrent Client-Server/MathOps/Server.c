#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORTNO 9999

float calc(float a, float b, char ch)
{
    switch (ch)
    {
    case '+':
        return a + b;
        break;

    case '-':
        return a - b;
        break;

    case '*':
        return a * b;
        break;

    case '/':
        return a / b;
        break;
    }
}
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
    server.sin_addr.s_addr = inet_addr("192.168.33.143");
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

    while (1)
    {
        new_server_socket = accept(server_socket, (struct sockaddr *)&client, &clilen);

        if (fork() == 0)
        {
            float a, b;
            char ch;

            recv(new_server_socket, &a, sizeof(a), 0);
            recv(new_server_socket, &b, sizeof(b), 0);
            recv(new_server_socket, &ch, sizeof(ch), 0);

            float result = calc(a, b, ch);
            send(new_server_socket, &result, sizeof(result), 0);
        }

        close(new_server_socket);
    }

    close(server_socket);
}