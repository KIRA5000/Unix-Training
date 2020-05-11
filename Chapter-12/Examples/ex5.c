#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;
void prepare()
{
	printf("Prepare..\n");
	pthread_mutex_lock(&m);
}
void parent()
{
	printf("Parent..\n");
	pthread_mutex_unlock(&m);
}
void child()
{
	printf("Child..\n");
	pthread_mutex_unlock(&m);
}
void *thread(void *arg)
{
	pthread_mutex_lock(&m);
	printf("Mutex locked by thread\n");
	sleep(10);
	pthread_mutex_unlock(&m);
}
int main(void)
{
	pthread_t tid;
	printf("Creating thread\n");
	pthread_create(&tid,NULL,thread,NULL);
	sleep(1);
	pthread_atfork(prepare,parent,child);
	printf("Creating child\n");
	pid_t pid=fork();
	if(pid==0)
	{
		printf("Child ran\n");
	}
	else
	{
		printf("Parent ran\n");
	}
	return 0;
}
