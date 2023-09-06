#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct threadAttribute
{
	int start, end;
} Attributes;

int isPrime(int num)
{
	int count=0;

	for(int i=1;i<=num;i++)
	{
		if(num%i==0)
			count++;
	}

	if(count==2)
		return 1;
	return 0;
}

void* displayPrime(void *arg)
{
	Attributes *attr = (Attributes*) arg;

	int *result;
	int k=0;

	for(int i=attr->start;i<=attr->end;i++)
	{
		printf("%d ",i);
		if(isPrime(i))
			*(result+k)=i;
	}

	for(int i=attr->start;i<=attr->end;i++)
	{
		printf("%d ",result[i]);
	}

	// return (void*)result;
}

void main(int argc, char *argv[])
{
	int a,b;
	printf("Enter starting and ending numbers : ");
	scanf("%d%d",&a,&b);

	Attributes attr;
	attr.start=a;
	attr.end=b;

	int *res;

	pthread_t thread;
	pthread_create(&thread,0,displayPrime,(void*)&attr);

	// pthread_join(thread,(void**)&res);
	pthread_join(thread,0);

	// for(int i=attr.start;i<=attr.end;i++)
	// {
	// 	printf("%d ",res[i]);
	// }
}