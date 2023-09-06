#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct threadAttribute
{
	int size;
	int *arr;
} Attributes;

void* posSum(void *arg)
{
	Attributes *att = (Attributes*) arg;

	int sum=0;

	for(int i=0;i<att->size;i++)
		printf("%d ",att->arr[i]);

	for(int i=0;i<att->size;i++)
	{
		if(att->arr[i]>0)
		{
			sum+=att->arr[i];
		}
	}

	return (void*)sum;
}

void main(int argc, char *argv[])
{
	int arr[]={1,9,-9,12,-5,3};
	int sum;

	Attributes attr;
	attr.size = sizeof(arr)/sizeof(arr[0]);
	attr.arr=arr;

	pthread_t thread;
	pthread_create(&thread,0,&posSum,(void*)&attr);

	pthread_join(thread,(void**)&sum);

	printf("\nSum of non-negative numbers = %d\n",sum);
}