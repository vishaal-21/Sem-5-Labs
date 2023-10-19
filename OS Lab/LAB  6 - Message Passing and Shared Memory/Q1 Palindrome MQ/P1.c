#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#define filepath "/home/student/Desktop/210905037_OS/Week6/P1.c"

typedef struct
{
    long int msgtype;
    int num;
} Message;

void main()
{
    int n,res;

    int msgflag = IPC_CREAT | 0666;
    key_t key = ftok(filepath, 'A');
    int msgid = msgget(key, msgflag);

    Message message;
    message.msgtype = 1;

    printf("Enter a number : ");
    scanf("%d", &n);
    message.num = n;

    if (res = msgsnd(msgid, &message, sizeof(message.num), 0)==0)
    {
        printf("Message sent\n");
    }
}