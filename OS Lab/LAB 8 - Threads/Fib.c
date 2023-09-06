#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void* generate_fib(void *arg)
{
	int size=(int)arg;

	int first=0;
	int second=1;
	int third;

	int *result = malloc(size*sizeof(int));
	result[0]=0;
	result[1]=1;

	for(int i=2;i<size;i++)
	{
		third=first+second;
		result[i]=third;

		first=second;
		second=third;
	}

	return (void*)result;
}

void main(int argc, char *argv[])
{
	int n = atoi(argv[1]);
	int *resultArr = malloc(n*sizeof(int));

	pthread_t thread;
	pthread_create(&thread,0,generate_fib,(void*)n);

	pthread_join(thread,(void**)&resultArr);

	for(int i=0;i<n;i++)
		printf("%d ",resultArr[i]);
}