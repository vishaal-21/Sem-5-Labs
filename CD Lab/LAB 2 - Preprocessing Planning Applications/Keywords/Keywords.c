#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void main()
{
	FILE *f1;

	f1 = fopen("Input.c", "r");
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

	char str[25]="";
	char ch = fgetc(f1);
	int k;
	int i=0;

	while (ch != EOF)
	{
		if (ch >= 97 && ch <= 122)
		{
			 while (ch >= 97 && ch <= 122)
			{
				str[i++]=ch;
				ch = fgetc(f1);
			}
			str[i]='\0';

			for (k = 0; k < 32; k++)
			{
				if (strcmp(keywords[k], str) == 0)
				{
					printf("%s ", strupr(str));
				}
			}
			
			strcpy(str,"");
		}
		
		i=0;
		ch=fgetc(f1);
	}

	fclose(f1);
}