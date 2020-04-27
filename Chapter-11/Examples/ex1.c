#include<stdio.h>
#include<pthread.h>
#include<errno.h>
#include<unistd.h>
pthread_t ntid;
void print(char *name)
{
	printf("%s: %d %ld\n",name,getpid(),pthread_self());
}
void *thread()
{
	print("new thread");
	return (void *)0;
}
int main(void)
{
	if(pthread_create(&ntid,NULL,thread,NULL)!=0)
	{
		perror("Thread Create");
	}
	else
	{
		sleep(1);
		print("main");
	}
	return 0;
}
