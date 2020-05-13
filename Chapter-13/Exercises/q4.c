#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<syslog.h>
#include<sys/signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/resource.h>
#include<pthread.h>
/*#define LOCKFILE "/var/run/daemon.pid"
#define LOCKMODE (S_IRUSR|S_IWUSR|S_IRGRP|S_TROTH)
int running(void)
{
	int fd;
	if((fd=open(LOCKFILE,O_RDWR|O_CREAT,LOCKMODE))<0)
	{
		syslog(LOG|ERR,"Daemon alread exists %m\n");
		exit(1);
	}
}*/
void *sgnl(void *arg)
{
	int num;
	sigset_t bmask;
	sigfillset(&bmask);
	while(1)
	{
		sigwait(&bmask,&num);
		switch(num)
		{
			case SIGTTOU:
				syslog(LOG_INFO,"SIGTTOU recieved");
				break;
			case SIGHUP:
				syslog(LOG_INFO,"SIGHUP recieved\n");
				break;
			case SIGTERM:
				syslog(LOG_INFO,"SIGTERM recieved, terminating");
				exit(0);
		}
	}
}
void daemonize(char *cmd)
{
	struct rlimit rl;
	umask(0);
	signal(SIGHUP,SIG_IGN);
	int fd0,fd1,fd2;
	if(getrlimit(RLIMIT_NOFILE,&rl)<0)
	{
		exit(127);
	}
	int pid;
	pid=fork();
	if(pid!=0)
	{
		exit(0);
	}
	else
	{
		sleep(1);
		openlog(cmd,LOG_CONS,LOG_DAEMON);
		setsid();
		if(chdir("/")<0)
		{
			exit(127);
		}
		for(int i=0;i<1024;i++)
			close(i);
		fd0=open("/dev/null",O_RDWR);
		fd1=dup(0);
		fd2=dup(1);
		if(fd0!=0||fd1!=1||fd2!=2)
		{
			syslog(LOG_ERR,"Unexpected fd :%d %d %d\n",fd0,fd1,fd2);
			exit(1);
		}
	}
}
int main(int argc,char *argv[])
{
	pthread_t tid;
	char *cmd;
	sigset_t bmask,omask;
	cmd=argv[0];
	daemonize(cmd);
	char *name;
	name=getlogin();
	int fd=open("/home/kira5000/Desktop/hello.txt",O_WRONLY|O_CREAT,0755);
	write(fd,name,50);
	sigfillset(&bmask);
	pthread_sigmask(SIG_SETMASK,&bmask,&omask);
	signal(SIGHUP,SIG_DFL);
	//pthread_create(&tid,NULL,sgnl,NULL);
	//pthread_join(tid,NULL);
	return 0;
}
