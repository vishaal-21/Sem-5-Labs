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

void displayToken(Token token)
{
    // printf("<%s , %s , %d , %d>\n", token.type, token.token_name, token.row_no, token.column_no);
    printf("< %s , %s >\n", token.type, token.token_name);
}
void removePreprocessorDirectivesAndComments(FILE *f1, FILE *f2)
{
    char line[256];

    char ch = fgetc(f1);

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
Token getAllOperators(FILE *f)
{
    Token token;

    fseek(f, -2, SEEK_CUR);
    char ch0 = fgetc(f);
    char ch1 = fgetc(f);
    char ch2 = fgetc(f);

    // printf("%c %c %c",ch0,ch1,ch2);

    if (ch1 == '!' && ch2 == '=')
    {
        strcpy(token.type, "NE");
        strcpy(token.token_name, "!=");
        ind++;
    }
    if (ch1 == '<' && ch2 == '=')
    {
        strcpy(token.type, "LE");
        strcpy(token.token_name, "<=");
        ind++;
    }
    if (ch1 == '<' && isOtherRelop(ch2))
    {
        strcpy(token.type, "LT");
        strcpy(token.token_name, "<");
        ind++;
    }
    if (ch1 == '=' && ch2 == '=')
    {
        strcpy(token.type, "EQ");
        strcpy(token.token_name, "==");
        ind++;
    }
    if (ch1 == '>' && ch2 == '=')
    {
        strcpy(token.type, "GE");
        strcpy(token.token_name, ">=");
        ind++;
    }
    if (ch1 == '>' && isOtherRelop(ch2))
    {
        strcpy(token.type, "GT");
        strcpy(token.token_name, ">");
        ind++;
    }
    if (ch1 == '=' && isOtherRelop(ch2) && isOtherRelop(ch0))
    {
        strcpy(token.type, "Assignment");
        strcpy(token.token_name, "=");
        ind++;
    }
    if (ch1 == '+' && isOtherArithmop(ch2) && isOtherArithmop(ch0))
    {
        strcpy(token.type, "ADD");
        strcpy(token.token_name, "+");
        ind++;
    }
    if (ch1 == '-' && isOtherArithmop(ch2) && isOtherArithmop(ch0))
    {
        strcpy(token.type, "SUB");
        strcpy(token.token_name, "-");
        ind++;
    }
    if (ch1 == '/' && isOtherArithmop(ch2) && isOtherArithmop(ch0))
    {
        strcpy(token.type, "DIV");
        strcpy(token.token_name, "/");
        ind++;
    }
    if (ch1 == '*' && isOtherArithmop(ch2) && isOtherArithmop(ch0))
    {
        strcpy(token.type, "MUL");
        strcpy(token.token_name, "*");
        ind++;
    }
    if (ch1 == '%' && isOtherArithmop(ch2) && isOtherArithmop(ch0))
    {
        strcpy(token.type, "MOD");
        strcpy(token.token_name, "%");
        ind++;
    }
    if (ch1 == '&' && ch2 == '&')
    {
        strcpy(token.type, "Logical AND");
        strcpy(token.token_name, "&&");
        ind++;
    }
    if (ch1 == '|' && ch2 == '|')
    {
        strcpy(token.type, "Logical OR");
        strcpy(token.token_name, "||");
        ind++;
    }
    if (ch1 == '!' && isOtherLogop(ch2))
    {
        strcpy(token.type, "Logical NOT");
        strcpy(token.token_name, "!");
        ind++;
    }

    // token[ind].row_no = row;
    // token[ind].column_no = *i;

    return token;
}
Token getKeywordsAndIdentifiers(FILE *f)
{
    char word[256];
    char str[100];

    int j = 0;
    int argCount = 0;

    Token token;

    fseek(f, -1, SEEK_CUR);
    char ch = fgetc(f);

    while (isalpha(ch) || ch == '_')
    {
        word[j++] = ch;
        ch = fgetc(f);
    }
    fseek(f, -1, SEEK_CUR);
    word[j] = '\0';
    // printf("%s word\n", word);

    if (isKeyword(word))
    {
        strcpy(token.type, "KW");
        strcpy(token.token_name, word);
        // token[ind].row_no = row;
        // token[ind].column_no = *i - strlen(word);
        // ind++;
    }
    else if (!isKeyword(word))
    {
        int id = search(word, &list);

        if (id == 0)
        {
            identifier_count++;
            sprintf(str, "id-%d", identifier_count);
            strcpy(token.token_name, word);
            strcpy(token.type, str);
            // token[ind].row_no = row;
            // token[ind].column_no = *i - strlen(word);

            // int temp_i = *i;

            // symbol.index = identifier_count;
            // strcpy(symbol.symbolName, word);

            // if (line[*i] == '(')
            // {
            //     strcpy(symbol.type, "FUNC");

            //     if (strcmp(word, "printf") == 0)
            //     {
            //         strcpy(symbol.returnType, "int");
            //         sprintf(symbol.argNum, "%d", 1);
            //     }
            //     else
            //     {
            //         if (line[*i + 1] == ')')
            //         {
            //             sprintf(symbol.argNum, "%d", 0);
            //         }
            //         else
            //         {
            //             do
            //             {
            //                 temp_i++;

            //                 if (line[temp_i] == ',')
            //                     argCount++;

            //             } while (line[temp_i] != ')');

            //             argCount++;

            //             sprintf(symbol.argNum, "%d", argCount);
            //         }

            //         strcpy(symbol.returnType, token[ind - 1].token_name);
            //     }
            // }
            // else
            // {
            //     strcpy(symbol.type, token[ind - 1].token_name);
            //     strcpy(symbol.returnType, "--");
            //     sprintf(symbol.argNum, "%d", 0);
            // }

            // list = insert(symbol, list);
        }
        else
        {
            sprintf(str, "id-%d", id);
            strcpy(token.token_name, word);
            strcpy(token.type, str);
            // token[ind].row_no = row;
            // token[ind].column_no = *i - strlen(word);
        }

        ind++;
    }

    strcpy(word, "");
    j = 0;

    return token;
}
Token getStringLiterals(FILE *f)
{
    char lit[256];
    int j = 0;
    Token token;
    char ch = fgetc(f);

    // token.column_no = ftell(f);

    while (ch != '"')
    {
        lit[j++] = ch;
        ch = fgetc(f);
    }
    lit[j] = '\0';

    if (strlen(lit) != 0)
    {
        strcpy(token.type, "String Literal");
        strcpy(token.token_name, lit);
        // token.row_no = row;
        // ind++;
        strcpy(lit, "");
    }

    return token;
}
Token getCharacterLiterals(FILE *f)
{
    char lit[256];
    int j = 0;

    // token[ind].column_no = (*i)++;

    Token token;
    char ch=fgetc(f);

    while (ch != '\'')
    {
        lit[j++] = ch;
    ch=fgetc(f);
    }
    lit[j] = '\0';

    if (strlen(lit) != 0)
    {
        strcpy(token.type, "Character Literal");
        strcpy(token.token_name, lit);
        // token[ind].row_no = row;
        // ind++;
        strcpy(lit, "");
    }

    return token;
}
Token getNumericLiterals(FILE *f)
{
    char lit[256];
    int j = 0;
    Token token;

    // token[ind].column_no = *i;
    fseek(f, -1, SEEK_CUR);
    char ch = fgetc(f);

    while (isdigit(ch) || ch == '.')
    {
        lit[j++] = ch;
        ch = fgetc(f);
    }
    fseek(f, -1, SEEK_CUR);
    lit[j] = '\0';

    if (strlen(lit) != 0)
    {
        strcpy(token.type, "Numeric Literal");
        strcpy(token.token_name, lit);
        // token[ind].row_no = row;
        // ind++;
        strcpy(lit, "");
        // (*i)--;
    }

    return token;
}
Token getNextToken(FILE *f)
{
    Token token;

    char ch = fgetc(f);
    // printf("%c char\n", ch);

    while (isspace(ch))
        ch = fgetc(f);

    while (ch == '#')
    {
        do
        {
            ch = fgetc(f);
        } while (ch != '\n');
        ch = fgetc(f);
    }

    if (ch == '"')
        return getStringLiterals(f);
    else if (ch == '\'')
        return getCharacterLiterals(f);
    else if (isalpha(ch) || ch == '_')
        return getKeywordsAndIdentifiers(f);
    else if (isdigit(ch))
        return getNumericLiterals(f);
    else if (isSpecial(ch))
    {
        strcpy(token.type, "Special Symbol");
        token.token_name[0] = ch;
        token.token_name[1] = '\0';
        // token.row_no = row;
        // token.column_no = i;
        // ind++;

        return token;
    }
    else
        return getAllOperators(f);
}

void main()
{
    FILE *f1, *f2;
    char filename[100];

    // printf("Enter filename to generate tokens : ");
    // gets(filename);

    f1 = fopen("TokenInput.c", "r");
    f2 = fopen("Output.txt", "w");

    if (f1 == NULL)
    {
        printf("Cannot open file");
        exit(1);
    }

    removePreprocessorDirectivesAndComments(f1, f2);
    fclose(f2);

    f2 = fopen("Output.txt", "r");

    int i = 0;

    printf("TOKENS:\n\n");

    Token token = getNextToken(f2);
    // displayToken(token);
    while (token.token_name != NULL)
    {
        displayToken(token);
        token = getNextToken(f2);
        i++;

        if (i == 73)
            break;
    }
}