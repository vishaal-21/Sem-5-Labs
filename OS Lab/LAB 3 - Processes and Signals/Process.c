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
    
    if(pid==0){
        printf("This is child\n");
        printf("Child ID: %d\n", getpid());
        printf("Parent ID : %d\n", getppid());
        exit(1);
    }
    else{
        wait(&status);
        printf("\nThis is Parent");
        printf("\nChild ID: %d\n", pid);
        printf("Parent ID : %d\n", getpid());
    }
}