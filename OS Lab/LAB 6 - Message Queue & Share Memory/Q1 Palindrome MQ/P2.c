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
    int n, res;

    int msgflag = IPC_CREAT | 0666;
    key_t key = ftok(filepath, 'A');
    int msgid = msgget(key, msgflag);

    Message message;

    if (res = msgrcv(msgid, &message, sizeof(message.num), 0, 0))
    {
        printf("Message received\n");
    }

    n = message.num;
    int rev = 0;

    while (n > 0)
    {
        rev = (rev * 10) + (n % 10);
        n = n / 10;
    }

    if (rev == message.num)
        printf("%d - Palindrome\n",message.num);
    else
        printf("%d - Not palindrome\n",message.num);
}