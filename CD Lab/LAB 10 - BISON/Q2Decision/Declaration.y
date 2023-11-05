%start program

%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror(char *s);
extern FILE *yyin;
%}

%union{
    char *identifier;
    char *keyword;
    char *symbol;
    char *op;
    int number;
}

%token<identifier> ID
%token<keyword> KEYWORD
%token<symbol> SPECIAL
%token<op> OP
%token<number> NUMBER

%%
program: KEYWORD KEYWORD SPECIAL SPECIAL SPECIAL declarations assign_stat SPECIAL{
    printf("First : %s",$1);
    printf("Second : %s",$2);
    }
        ;

declarations: data_type identifier_list SPECIAL declarations
            | 
            ;

data_type: KEYWORD 
        ;

identifier_list: ID id_prime
                ;

id_prime: SPECIAL identifier_list 
        |
        ;

assign_stat: ID OP assign_prime 
            ;

assign_prime: ID SPECIAL
            | 
            NUMBER SPECIAL
            ;
%%

void yyerror(char *s) 
{
    fprintf(stderr, "Error: %s\n", s);
}

void main()
{
    yyin=fopen("CorrectParseInput.c","r");

    if(yyparse()==0)
        printf("Parse successful\n");
    else
        printf("Unsuccessful\n");

    fclose(yyin);
}