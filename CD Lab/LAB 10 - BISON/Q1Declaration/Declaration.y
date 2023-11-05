%token KEYWORD ID NUMBER VOID MAIN INT CHAR OPENPAREN CLOSEPAREN OPENCURLY CLOSECURLY COMMA SEMICOLON OP
%start program

%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
void yyerror(char *s);
extern FILE *yyin;
%}

%%
program: VOID MAIN OPENPAREN CLOSEPAREN OPENCURLY declarations assign_stat CLOSECURLY
        ;

declarations: data_type identifier_list SEMICOLON declarations
            | 
            ;

data_type: INT 
        | CHAR
        ;

identifier_list: ID id_prime
                ;

id_prime: COMMA identifier_list 
        |
        ;

assign_stat: ID OP assign_prime 
            ;

assign_prime: ID SEMICOLON
            | 
            NUMBER SEMICOLON
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
        printf("Parse successful");
    else
        printf("Unsuccessful");

    fclose(yyin);
}

