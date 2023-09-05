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

        if(shelf>0)
        {
            shelf--;
            printf("Consumer consumed. Shelf has : %d\n",shelf);
        }
        else
            printf("\nWaiting for produce.");

        // sleep(8);
    }
    close(pipe_fd);
}