#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
void sig_hup(int signo)
{
	printf("HUP signal caught %d\n",getppid());
}
void print(char *name)
{
	printf("%s:%i %i %i %i\n",name,getpid(),getppid(),getpgrp(),tcgetpgrp(STDOUT_FILENO));
}
int main(void)
{
	char c;
	print("Parent");
	pid_t pid=fork();
	if(pid==0)
	{
		print("child");
		signal(SIGHUP,sig_hup);
		kill(getpid(),SIGSTOP);
		print("child");
		if(read(STDIN_FILENO,&c,1)!=1)
		{
			perror("read");
		}
	}
	else
	{
		sleep(2);
	}
	return 0;
}
