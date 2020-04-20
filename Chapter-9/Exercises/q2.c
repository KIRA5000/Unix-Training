#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
void print(char *name)
{
	printf("%s: %i %i %i %i\n",name,getpid(),getppid(),getpgrp(),getsid(getpid()));
	int i=(tcgetpgrp(STDOUT_FILENO)>0)?1:0;
	printf("Does it have controlling terminal:%d\n",i);
}
int main(void)
{
	print("parent");
	pid_t pid =fork();
	if(pid==0)
	{
		print("child");
		pid_t npid=setsid();
		printf("new session id:%d\n",npid);
		print("child");
	}
	else
	{
		wait(NULL);
	}
	return 0;
}
