#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
// /home/vishal/Sem-5-Labs

void listFilesRecursively(char str[])
{
    char path[1000];
    struct dirent *entry;
    DIR *dir = opendir(str);
    struct stat buf;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            lstat(entry->d_name,&buf);

            snprintf(path, sizeof(path), "%s/%s", str, entry->d_name);

            if (S_ISDIR(buf.st_mode))
            {
                printf("%s\n", path);
                listFilesRecursively(path);
            }
            else
            {
                printf("%s\n", path);
            }
        }
    }

    closedir(dir);
}

void main(int argc, char *argv[])
{
    DIR *d = opendir(argv[1]);
    if (d == NULL)
    {
        perror("Directory does not exist");
        exit(1);
    }

    chdir(argv[1]);

    listFilesRecursively(argv[1]);
}