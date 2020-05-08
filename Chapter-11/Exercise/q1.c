#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
struct foo
{
	int a,b,c,d;
};
void print(char *name,struct foo *fd1)
{
	printf("%s: %d %d %d %d\n",name,fd1->a,fd1->b,fd1->c,fd1->d);
}
void *thread1(void *arg)
{
	struct foo *fd=(struct foo *)malloc(sizeof(struct foo));
	fd->a=1;
	fd->b=2;
	fd->c=3;
	fd->d=4;
	print("thread1",fd);
	pthread_exit((void *)fd);
}
void *thread2(void *arg)
{
	return (void *)1;
}
int main(void)
{
	pthread_t tid1,tid2;
	struct foo *fd1;
	void *fd2;
	pthread_create(&tid1,NULL,thread1,NULL);
	pthread_join(tid1,(void *)&fd1);
	print("main",fd1);
	pthread_create(&tid2,NULL,thread2,NULL);
	pthread_join(tid2,&fd2);
	print("main",fd1);
	return 0;
}
