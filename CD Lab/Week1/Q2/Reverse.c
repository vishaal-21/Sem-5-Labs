#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *f1,*f2;
	char filename[100],ch;
	int i=-1;
	
	// printf("Enter source filename : ");
	// scanf("%s",filename);
	
	// f1=fopen(filename,"r");
	f1=fopen("Sample.txt","r");

	
	if(f1==NULL)
	{
		printf("Cannot open file");
		exit(0);
	}
	
	// printf("Enter destination filename : ");
	// scanf("%s",filename);
	
	f2=fopen("Destination.txt","w");

	while(fseek(f1,i--,SEEK_END)>=0){
		ch=fgetc(f1);
		fputc(ch,f2);
	}

	fclose(f1);
	fclose(f2);
}
