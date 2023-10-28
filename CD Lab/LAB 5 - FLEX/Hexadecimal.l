%{
#include<stdio.h>
%}

%%
[+]?[0-9]+ { printf("Hexadecimal : %X",atoi(yytext)); }
.;
%%

int yywrap(){ return 1; }

void main()
{
    yylex();
}