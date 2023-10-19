#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <ctype.h>
#include <unistd.h>
#define filepath "/home/vishal/Sem-5-Labs/OS Lab/LAB  6 - Message Passing and Shared Memory/Q2 Alphabet SHM"
#define SIZE 1024

void main()
{
    int shmflag = IPC_CREAT | 0666;
    key_t key = ftok(filepath, 'A');
    int shmid = shmget(key, SIZE, shmflag);

    char parent_ch;
    char *shared_data = (char *)shmat(shmid, NULL, 0);

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Error");
        exit(1);
    }
    else if (pid == 0)
    {
        char child_ch;

        while (*shared_data == child_ch)
            ;

        if (*shared_data >= 'a' && *shared_data <= 'z')
            child_ch = (*shared_data + 1 - 'a') % 26 + 'a';

        if (*shared_data >= 'A' && *shared_data <= 'Z')
            child_ch = (*shared_data + 1 - 'A') % 26 + 'A';

        *shared_data = child_ch;
    }
    else
    {
        printf("Enter an alphabet : ");
        scanf(" %c", &parent_ch);

        if (isalpha(parent_ch))
        {
            *shared_data = parent_ch;

            while (*shared_data == parent_ch)
                ;

            printf("Received : %c\n", *shared_data);
        }
    }

    shmdt(shared_data);
    shmctl(shmid, IPC_RMID, NULL);
}