#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
void main(int argc, char *argv[]){
    int f1,f2;
    char chr;

    f1=open("Input.txt",O_RDONLY);
    f2=open("Output.txt",O_WRONLY);

    if(f1<0){
        printf("Cannot open file");
        exit(1);
    }

    while(read(f1,&chr,1)){
        if(chr!=EOF){
            write(f2,&chr,1);
        }
    }
}
