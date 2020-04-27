#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
int i=0;
int count=0;
pthread_rwlock_t lock=PTHREAD_RWLOCK_INITIALIZER;
void *thread1(void *arg)
{
	pthread_rwlock_rdlock(&lock);
	printf("Read at 1:%i\n",i);
	sleep(2);
	pthread_rwlock_unlock(&lock);
	printf("Read lock over of 1\n");
	pthread_rwlock_wrlock(&lock);
	for(int i=0;i<5;i++)
	{
		count++;
		printf("count in 1:%dd\n",count);
		if(i==3)
		{
			printf("2 sec sleep at 1\n");
			sleep(2);
		}
	}
	pthread_rwlock_unlock(&lock);
	printf("Write lock over of 1\n");
	pthread_exit((void *)0);
}
void *thread2(void *arg)
{
        pthread_rwlock_rdlock(&lock);
        printf("Read at 2:%i\n",i);
        sleep(2);
        pthread_rwlock_unlock(&lock);
        printf("Read lock over of 2\n");
        pthread_rwlock_wrlock(&lock);
        for(int i=0;i<5;i++)
        {
                count++;
		printf("Count in 2:%d\n",count);
                if(i==3)
                {
                        printf("2 sec sleep at 1\n");
                        sleep(2);
                }
        }
        pthread_rwlock_unlock(&lock);
        printf("Write lock over of 2\n");
        pthread_exit((void *)0);
}
int main(void)
{
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_create(&tid2,NULL,thread2,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("Back to main\n");
	return 0;
}
