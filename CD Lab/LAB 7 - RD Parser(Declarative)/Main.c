#include <stdlib.h>
#include "SymbolTableModified.c"

Token token[256];
int tok_no = 0;
int decl_flag = 1;

Token getNextToken()
{
    return token[++tok_no];
}
void invalid()
{
    printf("Parse Unsuccessful\n");
    printf("Error at row %d and column %d\n", token[tok_no - 1].row_no, token[tok_no - 1].column_no);
    // exit(0);
}

void data_type()
{
    char *data = getNextToken().token_name;

    if (strcmp(data, "int") == 0 || strcmp(data, "char") == 0)
        return;
    else
    {
        --tok_no;
        decl_flag = 0;
    }
}

void id_list();

void listPrime()
{
    if (strcmp(getNextToken().token_name, ",") == 0)
        id_list();
    else
        --tok_no;
}

void id_list()
{
    if (decl_flag && strstr(getNextToken().type, "id") != NULL)
        listPrime();
}

void declaration()
{
    data_type();
    id_list();
    if (decl_flag && strcmp(getNextToken().token_name, ";") == 0)
        declaration();
}

void assignPrime()
{
    char *type = getNextToken().type;
    if (strstr(type, "id") != NULL)
    {
        if (strcmp(getNextToken().token_name, ";") == 0)
            return;
    }
    else if (strstr(type, "Numeric") != NULL)
    {
        if (strcmp(getNextToken().token_name, ";") == 0)
            return;
    }
    else
        invalid();
}

void assignment()
{
    if (strstr(getNextToken().type, "id") != NULL)
    {
        if (strcmp(getNextToken().token_name, "=") == 0)
            assignPrime();
        else
            invalid();
    }
}

void program()
{
    if (strcmp(getNextToken().token_name, "main") == 0)
    {
        if (strcmp(getNextToken().token_name, "(") == 0)
        {
            if (strcmp(getNextToken().token_name, ")") == 0)
            {
                if (strcmp(getNextToken().token_name, "{") == 0)
                {
                    declaration();
                    assignment();

                    if (strcmp(getNextToken().token_name, "}") == 0)
                        printf("Parse Successful");
                    else
                    {
                        invalid();
                        printf("Missing parentheses '\n");
                        exit(0);
                    }
                }
                else
                {
                    invalid();
                    printf("Missing parentheses '{'\n");
                    exit(0);
                }
            }
            else
            {
                invalid();
                printf("Missing parentheses ')'\n");
                exit(0);
            }
        }
        else
        {
            invalid();
            printf("Missing parentheses '('\n");
            exit(0);
        }
    }
    else
        invalid();
}
void main()
{
    FILE *f1, *f2;
    char filename[100];

    char line[256];

    printf("Enter filename to parse : ");
    gets(filename);

    f1 = fopen(filename, "r");
    f2 = fopen("Output.txt", "w");

    if (f1 == NULL)
    {
        printf("Cannot open file");
        exit(1);
    }

    removePreprocessorDirectivesAndComments(f1, f2);
    fclose(f2);

    f2 = fopen("Output.txt", "r");

    while (fgets(line, sizeof(line), f2))
    {
        row++;

        if (strstr(line, "include") != NULL || strstr(line, "define") != NULL)
            continue;

        generateTokens(line, token);
    }

    printf("TOKENS:\n\n");
    displayToken(token);
    printf("\n\n");

    program();
}