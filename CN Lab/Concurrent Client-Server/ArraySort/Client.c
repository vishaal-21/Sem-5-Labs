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

    int n;
    printf("Enter array size: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter %d numbers : ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    send(sockfd, &n, sizeof(n), 0);
    send(sockfd, a, sizeof(a), 0);

    int pid;
    recv(sockfd, &pid, sizeof(pid), 0);

    int sort[n];
    recv(sockfd, sort, sizeof(sort), 0);

    printf("Sorted array with PID %d: ", pid);
    for (int i = 0; i < n; i++)
        printf("%d ", sort[i]);

    close(sockfd);
}
