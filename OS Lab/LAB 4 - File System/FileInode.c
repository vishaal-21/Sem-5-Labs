#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include<string.h>

void main(int argc, char *argv[])
{
    char filepath[100];

    printf("Enter file path : ");
    gets(filepath);

    struct stat buf;
    stat(filepath,&buf);

    printf("Inode number of file is : %ld\n",buf.st_ino);
}