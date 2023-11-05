%{
#include "Declaration.tab.h"
%}

%%
"#"[^"\n"]*
"//"(.)*"\n"
"/*"(.)*"*/\n"

[-+]?[0-9]+"."?[0-9]+ {  return NUMBER; } 

"void" { return VOID; }
"main" { return MAIN; }
"int" { return INT; }
"char" { return CHAR; }
"(" { return OPENPAREN; }
")" { return CLOSEPAREN; }
"{" { return OPENCURLY; }
"}" { return CLOSECURLY; }
";" { return SEMICOLON; }
"," { return COMMA; }
"=" { return OP; }

[A-Za-z_][a-zA-Z_0-9]* {  return ID; }
%%

int yywrap(){ return 1; }