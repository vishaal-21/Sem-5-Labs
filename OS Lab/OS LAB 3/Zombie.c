#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
void main()
{
    pid_t pid = fork();

    if (pid<0){
        printf("Child not created");
        exit(1);
    }

    if(pid>0)
        sleep(5);
    else        
        exit(0);
}