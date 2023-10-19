#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#define filepath "/home/student/Desktop/210905037_OS/Week6/Q3/Interface.c"
#define SIZE 1024

void main()
{
    key_t key = ftok(filepath, 'A');
    int shmflag = IPC_CREAT | 0666;
    int shmid = shmget(key, SIZE, shmflag);

    int *shared_data = (int*)shmat(shmid, NULL, 0);

    printf("%d",*shared_data);

    shmdt(shared_data);
}