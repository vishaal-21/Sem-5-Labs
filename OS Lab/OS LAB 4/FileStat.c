#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include<string.h>
#include<time.h>

void main(int argc, char *argv[])
{
    char filepath[100];
    time_t curr_time;
    time(&curr_time);

    printf("Enter file path : ");
    gets(filepath);

    struct stat buf;
    stat(filepath,&buf);

    printf("Stat Structure of file is : \n\n");

    printf("Inode number : %ld\n",buf.st_ino);
    printf("Block size : %ld\n",buf.st_blksize);
    printf("Create time : %s",ctime(&buf.st_ctime));
    printf("GID : %d\n",buf.st_gid);
    printf("UID : %d\n",buf.st_uid);
    printf("Size : %ld\n",buf.st_size);
    printf("Modification time : %s",ctime(&buf.st_mtime));
}