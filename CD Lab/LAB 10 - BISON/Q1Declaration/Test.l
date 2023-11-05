%{
#include<stdio.h>
#include<stdlib.h>

FILE *f2;
%}

%%
"#"[^"\n"]*
"//"(.)*"\n"
"/*"(.)*"*/\n"

"void" | "main" | "int" | "char" { fprintf(f2,"%s",yytext); }
[A-Za-z_][a-zA-Z_0-9]* { fprintf(f2, "%s",yytext); }
[ \t\n]+ { fprintf(f2,"%s",yytext); }
[(){}] { fprintf(f2,"%s",yytext); }
[;,] { fprintf(f2,"%s",yytext); }
"=" {fprintf(f2,"%s",yytext); }
[-+]?[0-9]+"."?[0-9]+ {fprintf(f2,"%s",yytext);} 

%%

int yywrap(){ return 1; }

void main()
{
    yyin=fopen("CorrectParseInput.c","r");

    f2=fopen("Output.txt","w");
    yylex();

}