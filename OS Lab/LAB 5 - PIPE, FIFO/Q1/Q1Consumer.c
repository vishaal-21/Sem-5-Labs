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
    
    int res;
    int nums[4];
    int bytes_read = 0;

    memset(nums, '\0', sizeof(nums));

    int pipe_fd = open(FIFO, O_RDONLY);

    if (pipe_fd != -1)
    {
        read(pipe_fd, nums, sizeof(nums));
        close(pipe_fd);
    }
    else
    {
        exit(1);
    }

    for(int i=0;i<4;i++)
        printf("%d ",nums[i]);

    printf("\nProcess %d finished\n", getpid());
    exit(1);
}