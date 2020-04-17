#include<stdio.h>
#include<unistd.h>
#include<signal.h>
sigset_t newmask,zeromask,oldmask;
static volatile int sigflag=0;
void sig_usr(int signo)
{
	sigflag=1;
}
void TELL_WAIT()
{
	signal(SIGUSR1,sig_usr);
	sigemptyset(&newmask);
	sigemptyset(&zeromask);
	sigaddset(&newmask,SIGUSR1);
	sigaddset(&newmask,SIGUSR2);
	sigaddset(&zeromask,SIGUSR2);
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);
}
void TELL_CHILD(pid_t pid)
{
	kill(pid,SIGUSR1);
}
void WAIT_PARENT()
{
	while(sigflag==0)
	{
		sigsuspend(&zeromask);
	}
	sigflag=0;
	sigprocmask(SIG_SETMASK,&oldmask,NULL);
}
int main(void)
{
	pid_t pid;
	TELL_WAIT();
	pid=fork();
	if(pid==0)
	{
		WAIT_PARENT();
		printf("Output from child\n");
	}
	else
	{
		printf("Output from parent\n");
		TELL_CHILD(pid);
	}
	return 0;
}
