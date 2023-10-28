%{
#include<stdio.h>
#include<string.h>

int scan_count=0;
int print_count=0;
%}

%%
"scanf" { scan_count++; printf("READ");}
"printf" { print_count++; printf("WRITE");}
. { putchar(yytext[0]); }
%%

int yywrap(){ return 1; }

void main()
{
    char filename[100];

    printf("Enter filename : ");
    gets(filename);

    FILE *f1 = fopen(filename,"r");

    yyin=f1;
    yylex();

    printf("Number of \"printf\" : %d\n",print_count);
    printf("Number of \"scanf\" : %d",scan_count);

    fclose(f1);
}