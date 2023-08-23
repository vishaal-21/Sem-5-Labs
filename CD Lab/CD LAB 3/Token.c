#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ind=0;
const char *keywords[] = {"auto",
							  "break",
							  "case",
							  "char",
							  "continue",
							  "do",
							  "default",
							  "const",
							  "double",
							  "else",
							  "enum",
							  "extern",
							  "for",
							  "if",
							  "goto",
							  "float",
							  "int",
							  "long",
							  "register",
							  "return",
							  "signed",
							  "static",
							  "sizeof",
							  "short",
							  "struct",
							  "switch",
							  "typedef",
							  "union",
							  "void",
							  "while",
							  "volatile",
							  "unsigned"};

typedef struct token{
	char token_name[100];
	int row_no;
	int column_no;
	char type[50];
}Token;

void removePreprocessorDirectivesAndComments(FILE *f1, FILE *f2)
{
	int flag=0;
	char line[256];
	
	while(fgets(line,256,f1))
	{
		char *res = strstr(line,"main");

		if(res!=NULL)
			flag=1;
		

		for(int i=0;i<strlen(line);i++)
		{	
			if((line[i]=='/'))
			{
				if(line[i+1]=='/')
				{
					do
					{
						i++;
					}while(line[i]!='\n');
				}
				else if(line[i+1]=='*')
				{
					do
					{
						i++;
					}while(line[i+1]!='*' && line[i+2]!='/');
				}
			}

			if(flag==1)
			{
				printf("%c",line[i]);
				fputc(line[i],f2);
			}
			else
			{
				if(line[i]=='#')
				{
					do
					{
						i++;
					}while(line[i]!='\n');
				}
			}
		}
	}
}

int isOtherRelop(char ch)
{
	if(ch!='>' || ch!='<' || ch!='=' || ch!='!')
		return 1;
	return 0;
}

int isOtherArithmop(char ch)
{
	if(ch!='+' || ch!='-' || ch!='/' || ch!='*' || ch!='%')
		return 1;
	return 0;
}

int isOtherLogop(char ch)
{
	if(ch!='&' || ch !='|' || ch!='!')
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

void getAllOperators(char line[],int row_no,Token token[])
{
	for(int i=0;i<strlen(line);i++)
	{
		//------------------------------------------relational operator-----------------------------------
		if(isOtherRelop(line[i]))
				continue;
		if(line[i] == '!' && line[i + 1] == '='){
			strcpy(token[ind].type, "RELOP : NE");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			strcpy(token[ind].token_name, "!=");
			ind++;
			i++;
		}
		if(line[i] == '<' && line[i + 1] == '='){
			strcpy(token[ind].type, "RELOP : LE");
			strcpy(token[ind].token_name, "<=");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '<' && isOtherRelop(line[i + 1])){
			strcpy(token[ind].type, "RELOP : LT");
			strcpy(token[ind].token_name, "<");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '=' && line[i + 1] == '='){
			strcpy(token[ind].type, "RELOP : EQ");
			strcpy(token[ind].token_name, "==");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '>' && line[i + 1] == '='){
			strcpy(token[ind].type, "RELOP : GE");
			strcpy(token[ind].token_name, ">=");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '>' && isOtherRelop(line[i + 1])){
			strcpy(token[ind].type, "RELOP : GT");
			strcpy(token[ind].token_name, ">");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}


		//------------------------------------arithmetic operator------------------------------------------
		if(isOtherArithmop(line[i]))
				continue;
		if(line[i] == '+' && isOtherArithmop(line[i + 1]) && isOtherArithmop(line[i - 1])){
			strcpy(token[ind].type, "ADD");
			strcpy(token[ind].token_name, "+");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '-' && isOtherArithmop(line[i + 1]) && isOtherArithmop(line[i - 1])){
			strcpy(token[ind].type, "SUB");
			strcpy(token[ind].token_name, "-");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '/' && isOtherArithmop(line[i + 1])){
			strcpy(token[ind].type, "DIV");
			strcpy(token[ind].token_name, "/");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '*' && isOtherArithmop(line[i + 1])){
			strcpy(token[ind].type, "MUL");
			strcpy(token[ind].token_name, "*");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
		if(line[i] == '%' && isOtherArithmop(line[i + 1])){
			strcpy(token[ind].type, "MOD");
			strcpy(token[ind].token_name, "%");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}


		//-----------------------------logical operator---------------------------------
		if(isOtherLogop(line[i]))
				continue;
		if(line[i] == '&' && line[i + 1] == '&'){
			strcpy(token[ind].type, "Logical AND");
			strcpy(token[ind].token_name, "&&");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '|' && line[i + 1] == '|'){
			strcpy(token[ind].type, "Logical OR");
			strcpy(token[ind].token_name, "||");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			i++;
		}
		if(line[i] == '!' && isOtherLogop(line[i + 1])){
			strcpy(token[ind].type, "Logical NOT");
			strcpy(token[ind].token_name, "!");
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
		}
	}
}

void getKeywords(char line[],int row,Token token[])
{
	char word[256];
	for(int i=0;i<strlen(line);i++)
	{
		int j=0;
		if (line[i] >= 97 && line[i] <= 122)
		{
			while (line[i] >= 97 && line[i] <= 122)
			{
				word[j++]=line[i];
				i++;
				j++;
			}
			word[j]='\0';

			if(isKeyword(word))
			{
				strcpy(token[ind].type,"KW");
				strcpy(token[ind].token_name,word);
				token[ind].row_no=row;
				token[ind].column_no=i - strlen(word);
				ind++;
			}

			strcpy(word,"");
			j=0;
		}
	}
}

void getSpecialSymbols(char line[],int row,Token token[])
{
	for(int i=0;i<strlen(line);i++)
	{
		if(line[i]=='$')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"$");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]=='{')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"{");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]=='}')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"}");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]=='[')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"[");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]==']')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"]");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]=='(')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"(");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]==')')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,")");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]=='.')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,".");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]==',')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,",");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]==':')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,":");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]==';')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,";");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]=='?')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"?");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]=='\'')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"'");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}

		if(line[i]=='"')
		{
			strcpy(token[ind].type,"Special Symbol");
			strcpy(token[ind].token_name,"");
			token[ind].row_no=row;
			token[ind].column_no=i;
			ind++;
		}
	}
}

void main(){
	FILE *f1,*f2;
	Token token[256];
	char line[256];

	f1=fopen("TokenInput.c","r");
	f2=fopen("TokenOutput.c","w");

	if(f1==NULL || f2==NULL){
		printf("Cannot open file");
		exit(1);
	}

	removePreprocessorDirectivesAndComments(f1,f2);
	int row=1;

	// while(fgets(line,256,f1))
	// {
	// 	getAllOperators(line,row,token);
	// 	getKeywords(line,row,token);
	// 	getSpecialSymbols(line,row,token);
	// 	//numeric and string literal
	// }

	// for(int i = 0; i < ind; i++){
	// 	printf("\n<%s, %s, %d, %d>", token[i].type, token[i].token_name,token[i].row_no, token[i].column_no);
	// }
}