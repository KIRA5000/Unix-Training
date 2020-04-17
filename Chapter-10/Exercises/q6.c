#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<fcntl.h>
sigset_t newmask,zeromask,oldmask;
static volatile int sigflag=0;
void sig_usr(int signo)
{
	sigflag=1;
}
void TELL_WAIT()
{
	signal(SIGCHLD,sig_usr);
	sigemptyset(&newmask);
	sigemptyset(&zeromask);
	sigaddset(&newmask,SIGCHLD);
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);
}
void WAIT_CHILD()
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
	int i=1;
	pid_t pid;
	int fd;
	TELL_WAIT();
	fd=open("q6.txt",O_WRONLY|O_APPEND|O_CREAT,0755);
	write(fd,"0\n",3);
	pid=fork();
	char wr[20];
	if(pid==0)	
	{
		printf("Child writting\n");
		sprintf(wr,"Child:%d\n",i++);
		write(fd,wr,20);
	}
	else
	{
		WAIT_CHILD();
		printf("Parent writting\n");
		sprintf(wr,"Parent:%d\n",i++);
		write(fd,wr,20);
		close(fd);
	}
	//close(fd);
	//printf("Termination\n");
	return 0;
}
