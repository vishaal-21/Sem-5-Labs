#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *thread_code(void *args)
{
	int num=(int) args;
	printf("Thread %d starting\n",num);
	return (void*)num;
}

void main()
{
	pthread_t thread[10];
	int return_val[10];

	for(int i=0;i<10;i++)
		pthread_create(&thread[i],0,&thread_code, (void*) i);

	for(int i=0;i<10;i++)
	{
		pthread_join(thread[i],(void**) &return_val[i]);
		printf("Thread %d ending\n",return_val[i]);
	}

}