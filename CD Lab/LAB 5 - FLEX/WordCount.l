%{
#include<stdio.h>
int words=0;
int chars=0;
int blanks=0;
int lines=0;
%}

%%
[a-zA-Z]+ {words++; chars+=strlen(yytext);}
[ ]+ {blanks++;}
.;
%%

void main()
{
	yylex();
	printf("Chars : %d\n",chars);
	printf("Words : %d\n",words);
	printf("Blanks : %d\n",blanks);
}

int yywrap(){ return 1; }