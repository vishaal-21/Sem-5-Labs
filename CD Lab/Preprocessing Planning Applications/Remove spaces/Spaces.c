#include<stdio.h>
#include<stdlib.h>
void main(){
	FILE *f1,*f2;
	char ch;

	f1=fopen("Input.txt","r");
	f2=fopen("Output.txt","w");

	if(f1==NULL || f2==NULL){
		printf("Cannot open file");
		exit(0);
	}

	ch=fgetc(f1);

	while(ch!=EOF){
		if(ch==' '){
			fputc(ch,f2);
			while(ch==' ')
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