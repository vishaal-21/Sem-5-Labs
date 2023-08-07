#include<stdio.h>
#include<stdlib.h>
void main()
{
	FILE *f1,*f2,*res;
	char ch1,ch2;
	f1=fopen("File1.txt","r");
	f2=fopen("File2.txt","r");

	if(f1==NULL || f2==NULL)
	{
		printf("Cannot open file");
		exit(0);
	}
	
	res=fopen("Result.txt","w");

	ch1=fgetc(f1);
	ch2=fgetc(f2);
	while(ch1!=EOF && ch2!=EOF)
	{
		while(ch1!='\n')
		{
			fputc(ch1,res);
			// printf("%c\n", ch1);
			ch1=fgetc(f1);
		}
		ch1=fgetc(f1);

		while(ch2!='\n')
		{
			fputc(ch2,res);
			// ch2=fgetc(f1);
			// printf("%c\n", ch2);
			ch2=fgetc(f2);
		}
		ch2=fgetc(f2);
	}

	fclose(f1);
	fclose(f2);
	fclose(res);
}
