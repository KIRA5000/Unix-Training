#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define NHASH 10
#define HASH(id) id%NHASH
struct foo
{
	int count;
	pthread_mutex_t lock;
	int id;
	struct foo *next;
};
struct foo *fh[NHASH];
pthread_mutex_t hashlock=PTHREAD_MUTEX_INITIALIZER;
struct foo *alloc(int id)
{
	printf("Alloc\n");
	struct foo *fp;
	int idx;
	if((fp=malloc(sizeof(struct foo)))!=NULL)
	{
		fp->count=1;
		fp->id=id;
		pthread_mutex_init(&fp->lock,NULL);
		idx=HASH(id);
		pthread_mutex_lock(&hashlock);
		fp->next=fh[idx];
		fh[idx]=fp;
		pthread_mutex_unlock(&hashlock);
	}
	return fp;
}
void hold(struct foo *fp)
{
	printf("Hold\n");
	pthread_mutex_lock(&fp->lock);
	fp->count++;
	pthread_mutex_unlock(&fp->lock);
}
struct foo *find(int id)
{
	struct foo *fp;
	int flag=0;
	printf("Find\n");
	pthread_mutex_lock(&hashlock);
	for(fp=fh[HASH(id)];fp!=NULL;fp=fp->next)
	{
		if(fp->id==id)
		{
			hold(fp);
			flag=1;
			break;
		}
	}
	if(flag==0)
	{
		fp=alloc(id);
	}
	pthread_mutex_unlock(&hashlock);
	return fp;
}
void rel(struct foo *fp)
{

}
void *thread1(void *arg)
{
	printf("Hello\n");
	fh[HASH(10)]=find(10);
	printf("Memory allocated for 10\n");
	rel(fh[HASH(1)]);
}
int main(void)
{
	fh[HASH(1)]=alloc(1);
	fh[HASH(2)]=alloc(2);
	fh[HASH(3)]=alloc(3);
	fh[HASH(4)]=alloc(4);
	fh[HASH(5)]=alloc(5);
	fh[HASH(6)]=alloc(6);
	fh[HASH(7)]=alloc(7);
	fh[HASH(8)]=alloc(8);
	fh[HASH(9)]=alloc(9);
	fh[HASH(0)]=alloc(0);
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_join(tid1,NULL);
//	pthread_create(tid2,NULL,thread2,NULL);

	return 0;
}
