#include <stdio.h>
// more random comments
#include <stdlib.h>
#define NUM 100

void main()
{
	// comment1
	// comment2
	int a = 7;
	float b_al = 10.2;
	char c = 'f';

#include <math.h>
#define A 50

	/*multiline1
	multiline2
	multiline3*/

	if (a < b_al && a + (b_al) >= 40)
		printf("#Works");
	else
		printf("#Does not work");

	printf("//Hello A");
	printf("/*Hello B*/");
}
int sum(int a, int b)
{
	return a + b;
}