#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_barrier_t b;
void *thread(void *i)
{
	printf("Before wait %ld\n",(long)i);
	printf("i: %ld return: %d\n",(long)i,pthread_barrier_wait(&b));
	printf("After wait %ld\n",(long)i);
}
int main()
{
	pthread_t tid[4];
	pthread_barrier_init(&b,NULL,4);
	for(long i=0;i<4;i++)
	{
		pthread_create(&tid[i],NULL,thread,(void *)i);
	}
	sleep(3);
	return 0;
}
