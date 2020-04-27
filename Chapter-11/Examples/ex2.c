#include<stdio.h>
#include<pthread.h>
void *thread1()
{
	printf("Entering thread1\n");
	return (void *)1;
}
void *thread2()
{
	printf("Entering thread2\n");
	pthread_exit((void*)2);
}
int main(void)
{
	void *rval;
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);
	pthread_join(tid1,&rval);
	printf("Thread1 return val:%ld\n",(long)rval);
	pthread_join(tid2,&rval);
	printf("Thread2 return val:%ld\n",(long)rval);
	return 0;
}
