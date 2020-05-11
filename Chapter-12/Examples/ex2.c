#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int done=1;
pthread_cond_t c=PTHREAD_COND_INITIALIZER;
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
void *thread(void *arg)
{
	pthread_mutex_lock(&m);
	sleep(3);
	printf("thread\n");
	done=0;
	pthread_mutex_unlock(&m);
	pthread_cond_signal(&c);
}
int main(void)
{
	pthread_t tid;
	pthread_create(&tid,NULL,thread,NULL);
	pthread_mutex_lock(&m);
	while(done==1)
	{
		pthread_cond_wait(&c,&m);
	}
	printf("main\n");
	return 0;
}
