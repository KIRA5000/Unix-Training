#include<stdio.h>
#include<signal.h>
#include<sys/wait.h>
#include<unistd.h>
void intr(int signo)
{
	printf("Interrupt handled\n");
}
void chld(int signo)
{
	printf("Child terminated\n");
}
int sys(char *cmd)
{
	pid_t pid;
	int status;
	sigset_t savechld,newchld;
	struct sigaction ignore,saveintr,savequit;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_handler=SIG_IGN;
	ignore.sa_flags=0;
	//sigaction(SIGINT,&ignore,&saveintr);
	sigaction(SIGQUIT,&ignore,&savequit);
	sigemptyset(&newchld);
	sigaddset(&newchld,SIGCHLD);
	//sigaddset(&newchld,SIGINT);
	sigprocmask(SIG_BLOCK,&newchld,&savechld);
	pid=fork();
	if(pid==0)
	{
		//sigaction(SIGINT,&ignore,&saveintr);
        	sigaction(SIGQUIT,&ignore,&savequit);
		execl("/bin/sh","sh","-c",cmd,(char *)0);
	}
	else
	{
		waitpid(pid,&status,0);
	}
	//sigaction(SIGINT,&saveintr,NULL);
        sigaction(SIGQUIT,&savequit,NULL);
	sigprocmask(SIG_SETMASK,&savechld,NULL);
	return(status);
}
int main(void)
{
	signal(SIGINT,intr);
	signal(SIGCHLD,chld);
	sys("/bin/ed");
	return 0;
}
