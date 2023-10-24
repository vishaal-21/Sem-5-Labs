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
int stmt_flag = 1;
int in_block = 0;
int offset = 1;

void expression();
void statement_list();

void invalid(char str[])
{
    printf("===========Parse Unsuccessful===============\n");
    printf("Error in function %s\n", str);
}
void parsed()
{
    printf("%s parsed\n",token.token_name);
}

void retract()
{
    fseek(f2, -strlen(token.token_name), SEEK_CUR);
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
        retract();
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
        retract();
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
        retract();
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
        retract();
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
        retract();
        assgn_flag = 0;
    }
}

void decision_prime()
{
    token = getNextToken(f2);
    parsed();

    if (strcmp(token.token_name, "else") == 0)
    {
        if (strcmp(getNextToken(f2).token_name, "{") == 0)
        {
            statement_list();

            if (strcmp(getNextToken(f2).token_name, "}") == 0)
                return;
            else
            {
                invalid("decision prime }");
                exit(1);
            }
        }
        else
        {
            invalid("decision prime {");
            exit(1);
        }
    }
    else
    {
        retract();
    }
}

void decision_stat()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "if") == 0)
    {
        if (strcmp(getNextToken(f2).token_name, "(") == 0)
        {
            expression();
            parsed();

            if (strcmp(getNextToken(f2).token_name, ")") == 0)
            {
                if (strcmp(getNextToken(f2).token_name, "{") == 0)
                {
                    statement_list();

                    if (strcmp(getNextToken(f2).token_name, "}") == 0)
                    {
                        printf("decision } parsed\n");
                        decision_prime();
                    }
                    else
                    {
                        invalid("decision }");
                        exit(1);
                    }
                }
                else
                {
                    invalid("decision {");
                    exit(1);
                }
            }
            else
            {
                invalid("decision )");
                exit(1);
            }
        }
        else
        {
            invalid("decision (");
            exit(1);
        }
    }
}

void looping_stat()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "while") == 0)
    {
        parsed();
        if (strcmp(getNextToken(f2).token_name, "(") == 0)
        {
            expression();

            if (strcmp(getNextToken(f2).token_name, ")") == 0)
            {
                if (strcmp(getNextToken(f2).token_name, "{") == 0)
                {
                    in_block++;
                    parsed();
                    statement_list();
                    printf("in while : %s\n", token.token_name);

                    if (strcmp(getNextToken(f2).token_name, "}") == 0)
                    {
                        parsed();
                        return;
                    }
                    else
                    {
                        invalid("loop }");
                        exit(1);
                    }
                }
                else
                {
                    invalid("loop {");
                    exit(1);
                }
            }
            else
            {
                invalid("loop )");
                exit(1);
            }
        }
        else
        {
            invalid("loop (");
            exit(1);
        }
    }
    else if (strcmp(token.token_name, "for") == 0)
    {
        if (strcmp(getNextToken(f2).token_name, "(") == 0)
        {
            parsed();
            assignment();

            if (strcmp(getNextToken(f2).token_name, ";") == 0)
            {
                parsed();
                expression();

                if (strcmp(getNextToken(f2).token_name, ";") == 0)
                {
                    parsed();
                    assignment();

                    if (strcmp(getNextToken(f2).token_name, ")") == 0)
                    {
                        parsed();
                        if (strcmp(getNextToken(f2).token_name, "{") == 0)
                        {
                            in_block++;
                            parsed();
                            statement_list();

                            if (strcmp(getNextToken(f2).token_name, "}") == 0)
                            {
                                parsed();
                                return;
                            }
                            else
                            {
                                invalid("loop }");
                                exit(1);
                            }
                        }
                        else
                        {
                            invalid("loop {");
                            exit(1);
                        }
                    }
                    else
                    {
                        invalid("floop )");
                        exit(1);
                    }
                }
                else
                {
                    invalid("floop ; 2");
                    exit(1);
                }
            }
            else
            {
                invalid("floop ; 1");
                exit(1);
            }
        }
        else
        {
            invalid("floop (");
            exit(1);
        }
    }
    else
    {
        invalid("loop");
        exit(1);
    }
}

void case_stmt()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "case") == 0)
    {
        parsed();
        token = getNextToken(f2);
        if (strcmp(token.type, "Numeric Literal") == 0)
        {
            parsed();
            token = getNextToken(f2);
            if (strcmp(token.token_name, ":") == 0)
            {
                parsed();

                printf("GOING FROM CASE STMT\n");
                statement_list();

                token = getNextToken(f2);
                if (strcmp(token.token_name, "break") == 0)
                {
                    parsed();
                    printf("here\n");
                    token = getNextToken(f2);

                    if (strcmp(token.token_name, ";") == 0)
                    {
                        parsed();
                        case_stmt();
                        return;
                    }
                }
            }
        }
    }
    else if(strcmp(token.token_name, "default") == 0)
    {
       parsed();
       
       token=getNextToken(f2);
        if (strcmp(token.token_name, ":") == 0)
        {
            parsed();

            printf("GOING FROM default CASE STMT\n");
            statement_list();
            return;
        } 
    }
}

void switch_stmt()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "switch") == 0)
    {
        parsed();
        token = getNextToken(f2);

        if (strcmp(token.token_name, "(") == 0)
        {
            parsed();
            token = getNextToken(f2);

            if (strstr(token.type, "id") != NULL)
            {
                parsed();
                token = getNextToken(f2);

                if (strcmp(token.token_name, ")") == 0)
                {
                    parsed();
                    token = getNextToken(f2);

                    if (strcmp(token.token_name, "{") == 0)
                    {
                        parsed();
                        in_block++;

                        case_stmt();

                        if (strcmp(getNextToken(f2).token_name, "}") == 0)
                            return;
                    }
                }
            }
        }
    }
}

// single line functions
void statement()
{
    token = getNextToken(f2);
    printf("stmt : %s %s\n", token.token_name, token.type);

    if (strstr(token.type, "id") != NULL)
    {
        stmt_flag = 1;
        retract();

        assignment();

        token = getNextToken(f2);
        printf("=> %s\n", token.token_name);

        if (strcmp(token.token_name, ";") == 0)
            return;
        else
        {
            offset = -1 * (strlen(token.token_name));
            fseek(f2, offset, SEEK_CUR);
        }
    }
    else if (strcmp(token.token_name, "if") == 0)
    {
        stmt_flag = 1;
        retract();

        decision_stat();
    }
    else if (strcmp(token.token_name, "for") == 0 || strcmp(token.token_name, "while") == 0)
    {
        stmt_flag = 1;
        retract();

        looping_stat();
    }
    else if (strcmp(token.token_name, "switch") == 0)
    {
        stmt_flag = 1;
        retract();

        switch_stmt();
    }
    else
    {
        // if (strcmp(token.token_name, "}") == 0)
        //     return;

        stmt_flag = 0;
        retract();
        // return;
    }
}

// single line functions
void statement_list()
{
    token=getNextToken(f2);
    if(token.token_name==NULL)
    {
        printf("NULL\n");
    }
    printf("in stmt list : %s\n",token.token_name);

    if(strstr(token.type,"id")!=NULL || strcmp(token.token_name,"if")==0 || strcmp(token.token_name,"for")==0 || strcmp(token.token_name,"while")==0 || strcmp(token.token_name,"switch")==0)
    {
        retract();

        statement();

        if (stmt_flag)
        {
            printf("recursive GOING FROM STMT LIST\n");
            statement_list();
        }
    }
    else
    {
        retract();
        return;
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
        rel_flag = 0;
        retract();
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
        retract();
        se_flag = 0;
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
        retract();
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
        retract();
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