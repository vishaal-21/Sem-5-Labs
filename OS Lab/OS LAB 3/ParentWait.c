#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void main()
{
    int status;
    pid_t pid = fork();

    if(pid==-1){
        perror("Child not created\n");
        exit(1);
    }
    else if(pid==0){
        printf("\nHello from CHILD\n");
        printf("Child ID : %d\n", getpid());
        printf("Parent ID : %d\n", getppid());
        exit(1);
    }
    else{
        wait(&status);
        printf("\nHello from PARENT");
        printf("\nParent ID : %d\n", getpid());
    }
}
