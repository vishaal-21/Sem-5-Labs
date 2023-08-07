#include<stdio.h>
#include<stdlib.h>
void main(){
	FILE *f1,*f2;

	f1=fopen("Input.c","r");
	f2=fopen("Output.c","w");

	if(f1==NULL || f2==NULL){
		printf("Cannot open file");
		exit(0);
	}

	char ch=fgetc(f1);
	while(ch!=EOF){
		if(ch=='#'){
			do{
				ch=fgetc(f1);
			}while(ch!='\n');
		}
		if(ch=='"'){
			do{
				fputc(ch,f2);
				ch=fgetc(f1);
			}while(ch!='"');
			fputc(ch,f2);
			ch=fgetc(f1);
		}
		else{
			fputc(ch,f2);
			ch=fgetc(f1);
		}
	}

	fclose(f1);
	fclose(f2);
}