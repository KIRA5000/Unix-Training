#include<stdio.h>
#include<sys/signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
int sign=0;
sigset_t nmask,omask,zmask;
void sig(int signo)
{
	sign=1;
}
void TELL_WAIT()
{
	signal(SIGUSR1,sig);
	signal(SIGUSR2,sig);
	sigemptyset(&zmask);
	sigemptyset(&nmask);
	sigaddset(&nmask,SIGUSR1);
	sigaddset(&nmask,SIGUSR2);
	sigprocmask(SIG_BLOCK,&nmask,&omask);
}
int wlock_set(int whence,int start,int len,pid_t pid,int fd)
{
	struct flock lk;
	lk.l_type=F_WRLCK;
	lk.l_whence=whence;
	lk.l_start=start;
	lk.l_len=len;
	lk.l_pid=pid;
	if(fcntl(fd,F_SETLKW,&lk)>=0)
	{
		printf("lock acquired for %d\n",start);
	}
	else
	{
		printf("lockfailed for %d\n",start);
		perror("fail");
	}
}
void TELL_PARENT(pid_t pid)
{
	kill(pid,SIGUSR2);
}
void WAIT_PARENT()
{
	while(sign==0)
	{
		sigsuspend(&zmask);
	}
	sign=0;
	sigprocmask(SIG_SETMASK,&omask,NULL);
}
void TELL_CHILD(pid_t pid)
{
	kill(pid,SIGUSR1);
}
void WAIT_CHILD()
{
	while(sign==0)
	{
		sigsuspend(&zmask);
	}
	sign=0;
	sigprocmask(SIG_SETMASK,&omask,NULL);
}
int main(void)
{
	int fd=open("/home/kira5000/Desktop/hello.txt",O_RDWR);
	pid_t pid;
	TELL_WAIT();
	if((pid=fork())<0)
	{
		printf("Error during fork()\n");
		exit(127);
	}
	else if(pid==0)
	{
		wlock_set(SEEK_SET,0,1,getpid(),fd);
		TELL_PARENT(getppid());
		WAIT_PARENT();
		wlock_set(SEEK_SET,1,1,getpid(),fd);
	}
	else
	{
		wlock_set(SEEK_SET,1,1,getpid(),fd);
		TELL_CHILD(pid);
		WAIT_CHILD();
		wlock_set(SEEK_SET,0,1,getpid(),fd);
	}
	return 0;
}
