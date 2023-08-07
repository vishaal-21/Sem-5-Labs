#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
void main(){
	FILE *f1;

	f1=fopen("Input.c","r");
	const char *keywords[] = {
	    "auto", 
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
	    "unsigned"
	};

	char str[256];
	char ch=fgetc(f1);
	int i=0;

	while(ch!=EOF){
		if(ch>=97 && ch<=122){
			do{
				printf("%c",ch);
				ch=fgetc(f1);
			}while(ch>=97 && ch<=122);
		}

		// printf("%s",str);

		for(int k=0;k<32;k++){
			if(strcmp(keywords[i],str)==0){
				// printf("%s",str);
			}
		}

		i=0;
	}

	fclose(f1);
}