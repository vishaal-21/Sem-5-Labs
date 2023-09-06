#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX 5
#define FIFO "/home/vishal/Sem-5-Labs/OS Lab/LAB 5 - PIPE, FIFO/fifo4"
void main()
{
    int shelf;

    int pipe_fd = open(FIFO, O_RDONLY);
    if(pipe_fd<0)
    {
        perror("Error");
        exit(1);
    }

    printf("Consumer starts\n");
    

    while(1)
    {
        read(pipe_fd,&shelf,sizeof(int));
        // printf("Added to shelf. Size : %d\n",shelf);

        if(shelf>0)
        {
            shelf--;
            printf("Consumer consumed. Shelf has : %d\n",shelf);
            sleep(3);
            write(pipe_fd,&shelf,sizeof(int));
        }
        else
            printf("\nWaiting for produce.");

    }
    close(pipe_fd);
}