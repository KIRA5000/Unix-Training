#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
int sys(char *cmd)
{
	pid_t pid=fork();
	if(pid==0)
	{
		execlp("/bin/sh","sh","-c",cmd,(char*)0);
	}
	else
	{
		waitpid(pid,NULL,0);
	}
	return 1;
}
int main()
{
	char cmd[100];
	printf("Enter command you wanna execute\n");
	scanf("%s",cmd);
	sys(cmd);
	return 0;
}
