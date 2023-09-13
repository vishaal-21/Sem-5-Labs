#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ind = 0;
char str[256];

void S();
void U();
void V();
void W();

void S()
{
    U();
    V();
    W();
}

void U()
{
    if (str[ind] == '(')
    {
        ind++;
        S();

        if (str[ind] == ')')
            ind++;
        else
        {
            printf("Invalid");
            exit(0);
        }
    }
    else if (str[ind] == 'a')
    {
        ind++;
        S();

        if (str[ind] == 'b')
            ind++;
        else
        {
            printf("Invalid");
            exit(0);
        }
    }
    else if (str[ind] == 'd')
        ind++;
    else
    {
        printf("Invalid");
        exit(0);
    }
}

void V()
{
    if (str[ind] == 'a')
    {
        ind++;
        V();
    }
}

void W()
{
    if (str[ind] == 'c')
    {
        ind++;
        W();
    }
}

void main()
{
    printf("ENTER STRING : ");
    gets(str);

    str[strlen(str)] = '$';

    S();

    if (str[ind] == '$')
        printf("Valid");
    else
        printf("Invalid");
}