#include<stdio.h>
#include<pthread.h>
void cleanup(void *name)
{
	printf("%s\n",(char *)name);
}
void *thread1(void *arg)
{
	printf("Thread1 started\n");
	pthread_cleanup_push(cleanup,"Thread1 1'st clean");
	pthread_cleanup_push(cleanup,"Thread1 2'nd clean");
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	printf("Thread1 exiting\n");
	pthread_exit((void *)1);
}
void *thread2(void *arg)
{
        printf("Thread2 started\n");
        pthread_cleanup_push(cleanup,"Thread2 1'st clean");
        pthread_cleanup_push(cleanup,"Thread2 2'nd clean");
        pthread_cleanup_pop(1);
        pthread_cleanup_pop(1);
        printf("Thread2 exiting\n");
        pthread_exit((void *)2);
}
int main(void)
{
	pthread_t tid1,tid2;
	int *rval;
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);
	pthread_join(tid1,(void *)&rval);
	printf("Thread1 returned:%d\n",rval);
	pthread_join(tid2,(void *)&rval);
	printf("Thread2 returned:%d\n",rval);
	return 0;
}
