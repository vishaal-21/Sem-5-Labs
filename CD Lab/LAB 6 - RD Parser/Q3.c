#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ind = 0;
char str[256];

void S();
void A();
void Aprime();
void B();

void S()
{
    if (str[ind] == 'a')
    {
        ind++;
        A();

        if (str[ind] == 'c')
        {
            ind++;
            B();

            if (str[ind] == 'e')
                ind++;
            else
            {
                printf("Invalid");
                exit(0);
            }
        }
        else
        {
            printf("Invalid");
            exit(0);
        }
    }
    else
    {
        printf("Invalid");
        exit(0);
    }
}

void A()
{
    if (str[ind] == 'b')
    {
        ind++;
        Aprime();
    }
}

void Aprime()
{
    if (str[ind] == 'b')
    {
        ind++;
        Aprime();
    }
}

void B()
{
    if (str[ind] == 'd')
        ind++;
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