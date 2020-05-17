#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
#define LOCKFILE "/home/kira5000/Desktop/hello1.txt"
int fd;
void TELL_WAIT()
{
	if((fd=open(LOCKFILE,O_WRONLY))<0)
	{
		printf("open error\n");
		exit(1);
	}
}
void WAIT_CHILD(pid_t pid,pid_t pid1)
{
	struct flock lk;
	lk.l_type=F_WRLCK;
	lk.l_whence=SEEK_SET;
	lk.l_start=0;
	lk.l_len=0;
	lk.l_pid=pid;
	fcntl(fd,F_SETLK,&lk);
	//printf("%d:%d\n",F_WRLCK,lk.l_type);
	//printf("2. fd:%d\n",lk.l_pid);
	lk.l_pid=pid1;
	fcntl(fd,F_SETLKW,&lk);
	//printf("2. fd:%d\n",lk.l_pid);
}
void TELL_CHILD(pid_t pid)
{
	struct flock lk;
        lk.l_type=F_UNLCK;
        lk.l_whence=SEEK_SET;
        lk.l_start=0;
        lk.l_len=0;
        lk.l_pid=pid;
	fcntl(fd,F_SETLK,&lk);
}
void TELL_PARENT(pid_t pid)
{
	struct flock lk;
        lk.l_type=F_UNLCK;
        lk.l_whence=SEEK_SET;
        lk.l_start=0;
        lk.l_len=0;
        lk.l_pid=pid;
	fcntl(fd,F_SETLK,&lk);
	printf("%d\n",lk.l_type);
	//printf("Hello\n");
        fcntl(fd,F_SETLK,&lk);
	//printf("%d:%d\n",F_UNLCK,lk.l_type);
	perror("unlock");
}
int main(void)
{
	TELL_WAIT();
	//printf("1. fd:%d\n",getpid());
	pid_t pid=fork();
	if(pid!=0)
	{
		printf("Parent start\n");
		WAIT_CHILD(pid,getpid());
		printf("After Child\n");
		TELL_CHILD(getpid());
	}
	else
	{
		sleep(1);
		printf("Child starts\n");
		//for(int i=0;i<300;i++);
		TELL_PARENT(getpid());
	}
	return 0;
}
