#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
struct shared
{
	int data;
	pthread_mutex_t lock;
};
struct shared sh;
void alloc()
{
	//sh=(struct shared *)malloc(sizeof(struct shared));
	pthread_mutex_init(&sh.lock,NULL);
	//return sh;
}
void lock()
{
	pthread_mutex_lock(&sh.lock);
}
void unlock()
{
	pthread_mutex_unlock(&sh.lock);
	//return sh;
}
void *thread1(void *arg)
{
	alloc();
	lock();
	sh.data=5;
	for(int i=0;i<5;i++)
	{
		sh.data++;
		if(i==3)
			sleep(2);
	}
	unlock();
	printf("sh->data:%d\n",sh.data);
	return (void *)0;
}
void *thread2(void *arg)
{
	sleep(1);
        //alloc(sh);
        lock();
        //sh.data=5;
        for(int i=0;i<5;i++)
		sh.data++;
        unlock();
        printf("sh->data:%d\n",sh.data);
	return (void *)0;
}
int main(void)
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);
	sleep(5);
}
