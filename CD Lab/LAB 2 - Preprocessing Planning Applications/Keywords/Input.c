#include<stdio.h>
#include<stdlib.h>
#define NUM 100
int main(){
	int a=10;
	float b=23.5;
	const char a = 'f';

	if(a>7)
		printf("%d",sizeof(a));

	return 0;
}