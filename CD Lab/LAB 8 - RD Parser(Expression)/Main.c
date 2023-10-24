#include <stdlib.h>
#include "SymbolTableV3.c"

FILE *f1, *f2;
Token token;
char *tok;
int decl_flag = 1;
int se_flag = 1;
int sp_flag = 1;
int assgn_flag = 1;
int rel_flag = 1;
int offset = 1;

void expression();

void invalid(char str[])
{
    printf("===========Parse Unsuccessful===============\n");
    printf("Error in function %s\n", str);
}

void data_type()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "int") == 0 || strcmp(token.token_name, "char") == 0)
    {
        decl_flag = 1;
        return;
    }
    else
    {
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
        decl_flag = 0;
    }
}

void id_list();

void listDoublePrime()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, ",") == 0)
    {
        id_list();
    }
    else
    {
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
    }
}

void listPrime()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, ",") == 0)
    {
        id_list();
    }
    else if (strcmp(token.token_name, "[") == 0)
    {
        token = getNextToken(f2);

        if (strcmp(token.type, "Numeric Literal") == 0)
        {
            token = getNextToken(f2);

            if (strcmp(token.token_name, "]") == 0)
            {
                listDoublePrime();
            }
            else
            {
                invalid("listPrime 1");
                exit(0);
            }
        }
        else
        {
            invalid("listPrime 2");
            exit(0);
        }
    }
    else
    {
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
    }
}

void id_list()
{
    if (decl_flag)
    {
        token = getNextToken(f2);

        if (strstr(token.type, "id") != NULL)
        {
            listPrime();
        }
    }
}

void declaration()
{
    data_type();
    id_list();
    token = getNextToken(f2);
    if (decl_flag && strcmp(token.token_name, ";") == 0)
    {
        declaration();
    }
    else
    {
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
    }
}

void assignment()
{
    token = getNextToken(f2);

    if (strstr(token.type, "id") != NULL)
    {
        assgn_flag = 1;

        if (strcmp(getNextToken(f2).token_name, "=") == 0)
        {
            expression();
        }
        else
        {
            invalid("assignment");
            exit(0);
        }
    }
    else
    {
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
        assgn_flag = 0;
    }
}

// single line functions
void statement()
{
    if (assgn_flag)
    {
        assignment();
        token = getNextToken(f2);
        if (strcmp(token.token_name, ";") == 0)
            return;
        else
        {
            offset = -1 * (strlen(token.token_name));
            fseek(f2, offset, SEEK_CUR);
        }
    }
}

// single line functions
void statement_list()
{
    statement();
    if (assgn_flag)
    {
        statement_list();
    }
}

void relop()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "==") == 0 || strcmp(token.token_name, "!=") == 0 || strcmp(token.token_name, ">=") == 0 || strcmp(token.token_name, "<=") == 0 || strcmp(token.token_name, ">") == 0 || strcmp(token.token_name, "<") == 0)
    {
        rel_flag = 1;
        return;
    }
    else
    {
        rel_flag == 0;
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
    }
}

void mulop()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "*") == 0 || strcmp(token.token_name, "/") == 0 || strcmp(token.token_name, "%") == 0)
    {
        se_flag = 1;
        return;
    }
    else
    {
        se_flag = 0;
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
    }
}

void addop()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "+") == 0 || strcmp(token.token_name, "-") == 0)
    {
        sp_flag = 1;
        return;
    }
    else
    {
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
        sp_flag = 0;
    }
}

void factor()
{
    token = getNextToken(f2);
    if (strstr(token.type, "id") != NULL)
        return;
    else if (strstr(token.type, "Numeric") != NULL)
        return;
    else
    {
        offset = -1 * (strlen(token.token_name));
        fseek(f2, offset, SEEK_CUR);
    }
}

void term_prime()
{
    mulop();
    if (se_flag)
    {
        factor();
        term_prime();
    }
}

void term()
{
    factor();
    term_prime();
}

void simple_prime()
{
    addop();
    if (sp_flag)
    {
        term();
        simple_prime();
    }
}

void simple_expression()
{
    term();
    simple_prime();
}

void expn_prime()
{
    relop();
    if (rel_flag)
    {
        simple_expression();
    }
}

void expression()
{
    simple_expression();
    expn_prime();
}

void program()
{
    token = getNextToken(f2);

    token = getNextToken(f2);
    if (strcmp(token.token_name, "main") == 0)
    {
        token = getNextToken(f2);
        if (strcmp(token.token_name, "(") == 0)
        {
            token = getNextToken(f2);
            if (strcmp(token.token_name, ")") == 0)
            {
                token = getNextToken(f2);
                if (strcmp(token.token_name, "{") == 0)
                {
                    declaration();
                    statement_list();

                    if (strcmp(getNextToken(f2).token_name, "}") == 0)
                        printf("Parse Successful\n");
                    else
                    {
                        invalid("program1");
                        printf("Missing parentheses '}'\n");
                        exit(0);
                    }
                }
                else
                {
                    invalid("program2");
                    printf("Missing parentheses '{'\n");
                    exit(0);
                }
            }
            else
            {
                invalid("program3");
                printf("Missing parentheses ')'\n");
                exit(0);
            }
        }
        else
        {
            invalid("program4");
            printf("Missing parentheses '('\n");
            exit(0);
        }
    }
    else
        invalid("program5");
}
void main()
{
    char filename[100];

    // printf("Enter filename to generate tokens : ");
    // gets(filename);

    f1 = fopen("CorrectParseInput.c", "r");
    f2 = fopen("Output.txt", "w");

    if (f1 == NULL)
    {
        printf("Cannot open file");
        exit(1);
    }

    removePreprocessorDirectivesAndComments(f1, f2);
    fclose(f2);

    f2 = fopen("Output.txt", "r");

    program();
}