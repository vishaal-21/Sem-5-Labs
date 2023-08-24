#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
void main(int argc, char *argv[]){
    int f1;
    int i=0,line_no=0;
    char chr,ch[100];
    int flag=0;

    f1=open("Sample.txt",O_RDONLY);

    if(f1<0){
        printf("Cannot open file");
        exit(1);
    }

    while(read(f1,&chr,1)){
        if(chr!='\n')
            ch[i++]=chr;
        else{
            ch[i]='\0';
            i=0;
            line_no++;

            if(strstr(ch,argv[1])!=NULL){
                flag=1;
                printf("Line %d : %s\n",line_no,ch);
            }
        }
    }

    if(flag==0)
        printf("Word not found\n");
}
