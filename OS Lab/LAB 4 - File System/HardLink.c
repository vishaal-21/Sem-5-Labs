#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include<stdlib.h>

void main(int argc, char *argv[])
{
    char oldpath[100];
    char newpath[100];

    printf("Enter path of file to be linked : ");
    gets(oldpath);

    printf("Enter new path of linked file : ");
    gets(newpath);

    if(link(oldpath,newpath)<0)
    {
        perror("Error");
        exit(1);
    }
    printf("Linked.\n");

    // if(unlink(newpath)<0)
    // {
    //     perror("Error");
    //     exit(1); 
    // } 
    // printf("Unlinked.");
}