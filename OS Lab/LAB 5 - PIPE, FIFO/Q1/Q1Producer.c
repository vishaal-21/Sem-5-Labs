#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO "/home/vishal/Sem-5-Labs/OS Lab/LAB 5 - PIPE, FIFO/fifo"

int main()
{
    int bytes_sent = 0;

    int nums[4];

    printf("Enter 4 numbers : \n");
    for(int i=0;i<4;i++)
    {
        scanf("%d",&nums[i]);
    }

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

    if (pipe_fd != -1)
    {
        write(pipe_fd, nums, sizeof(nums));  
        close(pipe_fd);
    }
    else
    {
        exit(1);
    }

    printf("Process %d finished\n", getpid());
    exit(1);
}