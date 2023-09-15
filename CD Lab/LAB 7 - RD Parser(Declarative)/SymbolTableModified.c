#include <stdio.h>
#include "StructureDefinition.c"
#include <ctype.h>

int ind = 0;
int main_flag = 0;
int mlc_flag = 0;
int identifier_count = 0;
int row = 0;

TableElement *list = NULL;
Symbol symbol;

const char *keywords[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum",
                          "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static",
                          "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};

void displayToken(Token token[])
{
    for (int i = 0; i < ind; i++)
        printf("<%s , %s , %d , %d>\n", token[i].type, token[i].token_name, token[i].row_no, token[i].column_no);
}
void removePreprocessorDirectivesAndComments(FILE *f1, FILE *f2)
{
    char line[256];

    while (fgets(line, sizeof(line), f1))
    {
        char *res = strstr(line, "main");

        if (res != NULL)
            main_flag = 1;

        int insideQuotes = 0;

        for (int i = 0; i < strlen(line); i++)
        {
            if (line[i] == '"')
                insideQuotes = !insideQuotes;

            if (line[i] == '/' && line[i + 1] == '/' && !insideQuotes)
            {
                do
                {
                    i++;
                } while (line[i] != '\n');
            }

            else if (line[i] == '/' && line[i + 1] == '*' && !insideQuotes)
            {
                do
                {
                    i++;

                    if (line[i + 1] == '\n')
                    {
                        mlc_flag = 1;
                        break;
                    }
                } while (line[i + 1] != '*' && line[i + 2] != '/');
                break;
            }

            if (mlc_flag == 1)
            {
                while (line[i] != '\n')
                {
                    i++;

                    if (line[i] == '*' && line[i + 1] == '/')
                    {
                        mlc_flag = 0;
                        break;
                    }
                }
                break;
            }

            if (main_flag == 1)
            {
                fputc(line[i], f2);
            }
            else
            {
                if (line[i] == '#')
                // if(strstr(line,"import"))
                {
                    do
                    {
                        i++;
                    } while (line[i] != '\n');
                }
            }
        }
    }
}
int isSpecial(char ch)
{
    if (ch == '\'' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '$' || ch == '[' || ch == ']' || ch == '.' || ch == ',' || ch == ':' || ch == ';')
        return 1;
    return 0;
}
int isOtherRelop(char ch)
{
    if (ch != '>' && ch != '<' && ch != '=' && ch != '!')
        return 1;
    return 0;
}
int isOtherArithmop(char ch)
{
    if (ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '%')
        return 1;
    return 0;
}
int isOtherLogop(char ch)
{
    if (ch != '&' && ch != '|' && ch != '!')
        return 1;
    return 0;
}
int isKeyword(char str[])
{
    for (int k = 0; k < 32; k++)
    {
        if (strcmp(keywords[k], str) == 0)
            return 1;
    }
    return 0;
}
void getAllOperators(char line[], int *i, Token token[])
{
    if (line[*i] == '!' && line[*i + 1] == '=')
    {
        strcpy(token[ind].type, "NE");
        strcpy(token[ind].token_name, "!=");
        ind++;
        (*i)++;
    }
    if (line[*i] == '<' && line[*i + 1] == '=')
    {
        strcpy(token[ind].type, "LE");
        strcpy(token[ind].token_name, "<=");
        ind++;
        (*i)++;
    }
    if (line[*i] == '<' && isOtherRelop(line[*i + 1]))
    {
        strcpy(token[ind].type, "LT");
        strcpy(token[ind].token_name, "<");
        ind++;
    }
    if (line[*i] == '=' && line[*i + 1] == '=')
    {
        strcpy(token[ind].type, "EQ");
        strcpy(token[ind].token_name, "==");
        ind++;
        (*i)++;
    }
    if (line[*i] == '>' && line[*i + 1] == '=')
    {
        strcpy(token[ind].type, "GE");
        strcpy(token[ind].token_name, ">=");
        ind++;
        (*i)++;
    }
    if (line[*i] == '>' && isOtherRelop(line[*i + 1]))
    {
        strcpy(token[ind].type, "GT");
        strcpy(token[ind].token_name, ">");
        ind++;
    }
    if (line[*i] == '=' && isOtherRelop(line[*i + 1]) && isOtherRelop(line[*i - 1]))
    {
        strcpy(token[ind].type, "Assignment");
        strcpy(token[ind].token_name, "=");
        ind++;
    }
    if (line[*i] == '+' && isOtherArithmop(line[*i + 1]) && isOtherArithmop(line[*i - 1]))
    {
        strcpy(token[ind].type, "ADD");
        strcpy(token[ind].token_name, "+");
        ind++;
    }
    if (line[*i] == '-' && isOtherArithmop(line[*i + 1]) && isOtherArithmop(line[*i - 1]))
    {
        strcpy(token[ind].type, "SUB");
        strcpy(token[ind].token_name, "-");
        ind++;
    }
    if (line[*i] == '/' && isOtherArithmop(line[*i + 1]) && isOtherArithmop(line[*i - 1]))
    {
        strcpy(token[ind].type, "DIV");
        strcpy(token[ind].token_name, "/");
        ind++;
    }
    if (line[*i] == '*' && isOtherArithmop(line[*i + 1]) && isOtherArithmop(line[*i - 1]))
    {
        strcpy(token[ind].type, "MUL");
        strcpy(token[ind].token_name, "*");
        ind++;
    }
    if (line[*i] == '%' && isOtherArithmop(line[*i + 1]) && isOtherArithmop(line[*i - 1]))
    {
        strcpy(token[ind].type, "MOD");
        strcpy(token[ind].token_name, "%");
        ind++;
    }
    if (line[*i] == '&' && line[*i + 1] == '&')
    {
        strcpy(token[ind].type, "Logical AND");
        strcpy(token[ind].token_name, "&&");
        ind++;
        (*i)++;
    }
    if (line[*i] == '|' && line[*i + 1] == '|')
    {
        strcpy(token[ind].type, "Logical OR");
        strcpy(token[ind].token_name, "||");
        ind++;
        (*i)++;
    }
    if (line[*i] == '!' && isOtherLogop(line[*i + 1]))
    {
        strcpy(token[ind].type, "Logical NOT");
        strcpy(token[ind].token_name, "!");
        ind++;
    }

    token[ind].row_no = row;
    token[ind].column_no = *i;
}
void getKeywordsAndIdentifiers(char line[], int *i, Token token[])
{
    char word[256];
    char str[100];

    int j = 0;
    int argCount = 0;

    while (isalnum(line[*i]) || line[*i] == '_')
    {
        word[j++] = line[*i];
        (*i)++;
    }
    word[j] = '\0';

    if (isKeyword(word))
    {
        strcpy(token[ind].type, "KW");
        strcpy(token[ind].token_name, word);
        token[ind].row_no = row;
        token[ind].column_no = *i - strlen(word);
        ind++;
    }
    else if (!isKeyword(word))
    {
        int id = search(word, &list);

        if (id == 0)
        {
            identifier_count++;
            sprintf(str, "id-%d", identifier_count);
            strcpy(token[ind].token_name, word);
            strcpy(token[ind].type, str);
            token[ind].row_no = row;
            token[ind].column_no = *i - strlen(word);

            int temp_i = *i;

            symbol.index = identifier_count;
            strcpy(symbol.symbolName, word);

            if (line[*i] == '(')
            {
                strcpy(symbol.type, "FUNC");

                if (strcmp(word, "printf") == 0)
                {
                    strcpy(symbol.returnType, "int");
                    sprintf(symbol.argNum, "%d", 1);
                }
                else
                {
                    if (line[*i + 1] == ')')
                    {
                        sprintf(symbol.argNum, "%d", 0);
                    }
                    else
                    {
                        do
                        {
                            temp_i++;

                            if (line[temp_i] == ',')
                                argCount++;

                        } while (line[temp_i] != ')');

                        argCount++;

                        sprintf(symbol.argNum, "%d", argCount);
                    }

                    strcpy(symbol.returnType, token[ind - 1].token_name);
                }
            }
            else
            {
                strcpy(symbol.type, token[ind - 1].token_name);
                strcpy(symbol.returnType, "--");
                sprintf(symbol.argNum, "%d", 0);
            }

            list = insert(symbol, list);
        }
        else
        {
            sprintf(str, "id-%d", id);
            strcpy(token[ind].token_name, word);
            strcpy(token[ind].type, str);
            token[ind].row_no = row;
            token[ind].column_no = *i - strlen(word);
        }

        ind++;
        (*i)--;
    }

    strcpy(word, "");
    j = 0;
}
void getStringLiterals(char line[], int *i, Token token[])
{
    char lit[256];
    int j = 0;

    token[ind].column_no = (*i)++;

    while (line[*i] != '"')
    {
        lit[j++] = line[*i];
        (*i)++;
    }
    lit[j] = '\0';

    if (strlen(lit) != 0)
    {
        strcpy(token[ind].type, "String Literal");
        strcpy(token[ind].token_name, lit);
        token[ind].row_no = row;
        ind++;
        strcpy(lit, "");
    }
}
void getCharacterLiterals(char line[], int *i, Token token[])
{
    char lit[256];
    int j = 0;

    token[ind].column_no = (*i)++;

    while (line[*i] != '\'')
    {
        lit[j++] = line[*i];
        (*i)++;
    }
    lit[j] = '\0';

    if (strlen(lit) != 0)
    {
        strcpy(token[ind].type, "Character Literal");
        strcpy(token[ind].token_name, lit);
        token[ind].row_no = row;
        ind++;
        strcpy(lit, "");
    }
}
void getNumericLiterals(char line[], int *i, Token token[])
{
    char lit[256];
    int j = 0;

    token[ind].column_no = *i;
    while (isdigit(line[*i]) || line[*i] == '.')
    {
        lit[j++] = line[*i];
        (*i)++;
    }

    lit[j] = '\0';

    if (strlen(lit) != 0)
    {
        strcpy(token[ind].type, "Numeric Literal");
        strcpy(token[ind].token_name, lit);
        token[ind].row_no = row;
        ind++;
        strcpy(lit, "");
        (*i)--;
    }
}
void generateTokens(char line[], Token token[])
{
    int insideSingleQuotes = 0;

    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '"')
            getStringLiterals(line, &i, token);
        else if (line[i] == '\'')
            getCharacterLiterals(line, &i, token);
        else if (isalpha(line[i]) || line[i] == '_')
            getKeywordsAndIdentifiers(line, &i, token);
        else if (isdigit(line[i]))
            getNumericLiterals(line, &i, token);
        else if (isSpecial(line[i]))
        {
            strcpy(token[ind].type, "Special Symbol");
            token[ind].token_name[0] = line[i];
            token[ind].row_no = row;
            token[ind].column_no = i;
            ind++;
        }
        else
            getAllOperators(line, &i, token);
    }
}