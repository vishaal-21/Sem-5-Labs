%{
#include<stdio.h>
int pos=0;
int neg=0;
int posFloat=0;
int negFloat=0;
%}

%%
[+]?[0-9]+ { pos++; }
[-][0-9]+ { neg++; }
[+]?[0-9]+[.][0-9]+ { posFloat++; }
[-][0-9]+[.][0-9]+ { negFloat++; }
.;
%%

int yywrap(){ return 1; }

void main()
{
    yylex();
    printf("Positive Integers : %d\n",pos);
    printf("Negative Integers : %d\n",pos);
    printf("Positive Floating Numbers : %d\n",pos);
    printf("Negative Floating Numbers : %d\n",pos);
}