#include<stdio.h>
#include<fcntl.h>
#include<sys/signal.h>
#include<unistd.h>
#include<stdlib.h>
sigset_t nmask,omask,zmask;
int flag=0;
void sign(int signo)
{
	flag=1;
}
void TELL_WAIT()
{
	signal(SIGUSR1,sign);
	signal(SIGUSR2,sign);
	sigemptyset(&nmask);
	sigemptyset(&zmask);
	sigaddset(&nmask,SIGUSR1);
	sigaddset(&nmask,SIGUSR2);
	sigprocmask(SIG_BLOCK,&nmask,&omask);
}
void TELL_CHILD(pid_t pid)
{
	kill(pid,SIGUSR1);
}
void TELL_PARENT(pid_t pid)
{
        kill(pid,SIGUSR1);
}
void WAIT_CHILD()
{
	while(flag==0)
	{
		sigsuspend(&zmask);
	}
	flag=0;
	sigprocmask(SIG_SETMASK,&omask,NULL);
}
void WAIT_PARENT()
{
        while(flag==0)
        {
                sigsuspend(&zmask);
        }
        flag=0;
        sigprocmask(SIG_SETMASK,&omask,NULL);
}
int rlock_set(int start,int len,pid_t pid,int fd)
{
	struct flock lk;
	lk.l_type=F_RDLCK;
	lk.l_whence=SEEK_SET;
	lk.l_start=start;
	lk.l_len=len;
	lk.l_pid=pid;
	return fcntl(fd,F_SETLK,&lk);
}
int wlock_set(int start,int len,pid_t pid,int fd)
{
        struct flock lk;
        lk.l_type=F_WRLCK;
        lk.l_whence=SEEK_SET;
        lk.l_start=start;
        lk.l_len=len;
        lk.l_pid=pid;
        return fcntl(fd,F_SETLKW,&lk);
}
int lock_unset(int start,int len,pid_t pid,int fd)
{
        struct flock lk;
        lk.l_type=F_UNLCK;
        lk.l_whence=SEEK_SET;
        lk.l_start=start;
        lk.l_len=len;
        lk.l_pid=pid;
        return fcntl(fd,F_SETLKW,&lk);
}
int main(void)
{
	struct flock lk;
	pid_t pid;
	int fd=open("/home/kira5000/Desktop/hello1.txt",O_RDWR);
	TELL_WAIT();
	if((pid=fork())<0)
	{
		printf("Fork error\n");
		exit(0);
	}
	else if(pid!=0)
	{
		pid_t pid2=fork();
		if(pid2==0)
		{
			if(rlock_set(0,0,getpid(),fd)<0)
                	{
                        	printf("read lock of child2 error\n");
                        	perror("read lock");
                	}
                	else
                	{
                        	printf("Read lock success by child2\n");
                	}
			TELL_PARENT(getppid());
                	WAIT_PARENT();
                	if(lock_unset(0,0,getpid(),fd)<0)
                	{
                        	perror("unlock child2");
                	}
                	else
                	{
                        	printf("Unlock success by child2\n");
                	}
		}
		else
		{
			WAIT_CHILD();
			if(rlock_set(0,0,getpid(),fd)<0)
			{
				printf("read lock error\n");
				perror("read lock");
			}
			else
			{
				printf("Read lock success by parent\n");
			}
			TELL_CHILD(pid);
			WAIT_CHILD();
			if(lock_unset(0,0,getpid(),fd)<0)
			{
				perror("unlock parent");
			}
			else
			{
				printf("Unlock success by parent\n");
			}
			TELL_CHILD(pid2);
		}
			return 0;
	}
	else
	{
		WAIT_PARENT();
		if(wlock_set(0,0,getpid(),fd)<0)
		{
			perror("write lock child");
		}
		else
		{
			printf("Wriet lock Success by child\n");
		}
		if(lock_unset(0,0,getpid(),fd)<0)
                {
                        perror("unlock child");
                }
		else
		{
			printf("Unlock success by child\n");
		}
		TELL_PARENT(getppid());
	}
}
