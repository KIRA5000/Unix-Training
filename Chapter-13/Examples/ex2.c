#include<stdio.h>
#include<sys/signal.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int pid;
	pid=fork();
	if(pid!=0)
	{
		exit(0);
	}
	else
	{
		sleep(1);
		setsid();
		//char cmd[100];
		//sprintf(cmd,"ps -axj | grep %d",getpid());
		//system(cmd);
		sleep(10);
		return 0;
	}
}
