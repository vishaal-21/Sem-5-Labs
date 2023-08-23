#include<stdio.h>
#include<stdlib.h>
#define NUM 100 
void main()
{
	int a=7;
	float b=10.2;
	char c='f';

	if(a<b && a*b>=40)
		printf("#Works");
	else
		printf("#Does not work")
}