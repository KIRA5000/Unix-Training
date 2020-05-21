#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void)
{
	int fd[2];
	struct timeval tv;
	tv.tv_sec=1;
	tv.tv_usec=0;
	pipe(fd);
	fd_set rdset;
	FD_ZERO(&rdset);
	pid_t pid=fork();
	FD_SET(fd[0],&rdset);
	if(pid==0)
	{
		close(fd[1]);
		while(1)
		{
			int ret=select(fd[0]+1,&rdset,NULL,NULL,&tv);
			if(ret==1)
			{
				printf("Data ready to read\n");
				char rd[5];
				read(fd[0],rd,5);
			}
			else if(ret==0)
			{
				printf("Timeout\n");
				tv.tv_sec=1;
				tv.tv_usec=0;
			}
			else
			{
				perror("select");
				exit(1);
			}
		}
	}
	else
	{
		close(fd[0]);
		for(int i=0;i<3;i++)
		{
			write(fd[1],"hey\n",5);
			if(i==2)
			{
				close(fd[1]);
			}
			sleep(1);
		}
	}
	waitpid(pid,NULL,0);
	return 0;
}
