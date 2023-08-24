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
        printf("\nThis is child of Exec.c\n");
        printf("Child ID of Exec.c: %d\n", getpid());
        execlp("../ParentWait/wait","wait",NULL);
        exit(1);
    }
    else{
        wait(&status);
        printf("\nThis is Parent of Exec.c");
        printf("\nParent ID of Exec.c : %d\n", getpid());
    }
}