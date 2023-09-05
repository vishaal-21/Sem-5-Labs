#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX 5
#define FIFO "/home/vishal/Sem-5-Labs/OS Lab/LAB 5 - PIPE, FIFO/fifo4"
void main()
{
    int shelf=0;

    if (access(FIFO, F_OK) == -1)
    {
        int res = mkfifo(FIFO, 0777);
        if (res != 0)
        {
            perror("Could not create");
            exit(1);
        }
    }

    int pipe_fd = open(FIFO, O_WRONLY);

    if(pipe_fd<0)
    {
        perror("Error");
        exit(1);
    }

    printf("Producer starts\n");
    if(shelf<MAX)
    {
        shelf++;
        write(pipe_fd,&shelf,sizeof(int));
        printf("Producer added. Shelf has : %d\n",shelf);
    }

    // while(1)
    // {
    //     if(shelf<MAX)
    //     {
    //         shelf++;
    //         printf("Producer added. Shelf has : %d\n",shelf);
    //         write(pipe_fd,&shelf,sizeof(int));
    //     }
        
    //     sleep(2);
    // }
    close(pipe_fd);
}