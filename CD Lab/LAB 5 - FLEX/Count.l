%{
#include<stdio.h>
int vowelCount=0;
int consCount=0;
%}

%%

[aeiouAEIOU] {vowelCount++;}
[^aeiouAEIOU] {consCount++;}
.;

%%

void main()
{
	yylex();
	printf("V:%d\nC:%d\n",vowelCount,consCount);
}

int yywrap(){ return 1; }