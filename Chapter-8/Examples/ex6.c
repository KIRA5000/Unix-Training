#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<sys/wait.h>
int main(void)
{
	char *env[]={"Enviornment1=env1","Enviornment2=env2",NULL};
	pid_t pid=fork();
	if(pid==0)
	{
		execle("/home/kira5000/Desktop/Unix-Training/Chapter-8/Examples/ex5","arg1","arg2",(char *)0,env);
		_exit(0);
	}
	else
	{
		wait(NULL);
	}
	sleep(2);
	pid=fork();
	if(pid==0)
	{
		execlp("/home/kira5000/Desktop/Unix-Training/Chapter-8/Examples/ex5","arg1","arg2",(char*)0);
		perror("Execlp");
	}
	else
	{
		wait(NULL);
	}
	return 0;
}
