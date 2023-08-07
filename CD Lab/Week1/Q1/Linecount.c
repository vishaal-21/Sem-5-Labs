#include<stdio.h>
#include<stdlib.h>
void main(){
	FILE *f1;

	int linecount=0;
	int charcount=0;
	int sentence=0;
	int word=0;

	char filename[100],ch;

	printf("Enter source filename : ");
	scanf("%s",filename);

	f1=fopen(filename,"r");

	if(f1==NULL){
		printf("Cannot open file");
		exit(0);
	}

	ch=fgetc(f1);
	while(ch!=EOF){
		charcount++;
		if(ch=='\n')
			linecount++;

		else if(ch=='.')
			sentence++;

		else if(ch==' ')
			word++;
		ch=fgetc(f1);
	}

	printf("Number of characters : %d\n",charcount);
	printf("Number of lines : %d\n",linecount+1);
	printf("Number of sentences : %d\n",sentence);
	printf("Number of words : %d\n",word+1);

	fclose(f1);
}