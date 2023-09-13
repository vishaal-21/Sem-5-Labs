#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int ind = 0;
char str[256];

void S();
void T();
void Tprime();

void S()
{
    if (str[ind] == 'a' || str[ind] == '>')
        ind++;

    else if (str[ind] == '(')
    {
        ind++;
        T();

        if (str[ind] == ')')
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

void T()
{
    S();
    Tprime();
}

void Tprime()
{
    if (str[ind] == ',')
    {
        ind++;
        S();
        Tprime();
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