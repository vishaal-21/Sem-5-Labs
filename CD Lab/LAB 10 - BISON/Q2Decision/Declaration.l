%{
#include "Declaration.tab.h"

FILE *f2;
%}

%%
"#"[^"\n"]*
"//"(.)*"\n"
"/*"(.)*"*/\n"

"void" | "main" | "int" | "char" { yylval.keyword = strdup(yytext); return KEYWORD; }
[A-Za-z_][a-zA-Z_0-9]* { yylval.identifier = yytext; return ID; }
[ \t\n]+ 
[(){};,] { yylval.symbol = yytext; return SPECIAL; }
"=" { yylval.op = yytext; return OP; }
[-+]?[0-9]+"."?[0-9]+ { yylval.number = atoi(yytext); return NUMBER;} 

%%

int yywrap(){ return 1; }