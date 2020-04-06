#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>
int main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		execlp("/home/kira5000/Desktop/Unix-Training/Chapter-8/Examples/inter.txt","arg1","arg2",(char*)0);
		perror("execlp");
	}
	else
	{
		wait(NULL);
	}
	return 0;
}
