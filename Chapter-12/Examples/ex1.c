#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *thread(void *arg)
{
	printf("Hello thread1\n");
	return (void *)0;
}
int main(void)
{
	pthread_t tid;
	void *rval;
	pthread_attr_t atr;
	pthread_attr_init(&atr);
	pthread_attr_setdetachstate(&atr,PTHREAD_CREATE_DETACHED);
	pthread_create(&tid,&atr,thread,NULL);
	pthread_attr_destroy(&atr);
	//pthread_join(tid,&rval);
	sleep(1);
	return 0;
}
