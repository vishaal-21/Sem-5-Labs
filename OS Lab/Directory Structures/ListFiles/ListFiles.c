#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include<time.h>
void main(int argc, char *argv[])
{
    DIR *d;

    d = opendir(argv[1]);

    if (d == NULL)
    {
        printf("Directory not found");
        exit(1);
    }

    chdir(argv[1]);

    struct dirent *entry = readdir(d);
    struct stat buf;

    while (entry != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            entry = readdir(d);
            continue;
        }

        stat(entry->d_name, &buf);

        printf(S_ISDIR(buf.st_mode) ? "d" : "-");

        printf((buf.st_mode & S_IWUSR) ? "w" : "-");
        printf((buf.st_mode & S_IXUSR) ? "x" : "-");
        printf((buf.st_mode & S_IRUSR) ? "r" : "-");

        printf((buf.st_mode & S_IRGRP) ? "r" : "-");
        printf((buf.st_mode & S_IWGRP) ? "w" : "-");
        printf((buf.st_mode & S_IXGRP) ? "x" : "-");

        printf((buf.st_mode & S_IROTH) ? "r" : "-");
        printf((buf.st_mode & S_IWOTH) ? "w" : "-");
        printf((buf.st_mode & S_IXOTH) ? "x" : "-");

        printf("\t%ld\t%s\t%s\n", buf.st_size,ctime(&buf.st_mtime),entry->d_name);
        entry = readdir(d);
    }
}