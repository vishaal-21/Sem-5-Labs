#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
void sortArray(char *arr[], int size){
    char temp[256];

    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            if(strcmp(arr[j],arr[j+1])>0){
                strcpy(temp,arr[j]);
                strcpy(arr[j],arr[j+1]);
                strcpy(arr[j+1],temp);
            }
        }
    }
}
void main(int argc, char *argv[])
{
    DIR *d;
    int count = 0;
    char *arr[256];

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

        if (S_ISDIR(buf.st_mode))
        {
            arr[count] = entry->d_name;
            count++;
        }
        entry = readdir(d);
    }

    sortArray(arr,count);

    for(int i=0;i<count;i++)
        printf("%s\n",arr[i]);
}