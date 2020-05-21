#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/signal.h>
#include<stdlib.h>
extern char **environ;
void sign(int signo)
{
	printf("SIGPIPE caught\n");
	exit(12);
}
int main(void)
{
	pid_t pid;
	signal(SIGPIPE,sign);
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	pid=vfork();
	int n;
	FILE *fdin,*fdout;
	char line[100];
	if(pid>0)
	{
		close(fd1[0]);
		close(fd2[1]);
		fdin=fdopen(fd2[0],"r");
		setvbuf(fdin,NULL,_IONBF,0);
		fdout=fdopen(fd1[1],"w");
		setvbuf(fdout,NULL,_IONBF,0);
		while(fgets(line,100,stdin)!=NULL)
		{
			n=strlen(line);
			fputs(line,fdout);
			fgets(line,100,fdin);
			if(n==0)
			{
				break;
			}
			line[n]=0;
                	fputs(line,stdout);
		}
	}
	else
	{
		close(fd1[1]);
		close(fd2[0]);
		if(fd1[0]!=STDIN_FILENO)
		{
			dup2(fd1[0],STDIN_FILENO);
			close(fd1[0]);
		}
		if(fd2[1]!=STDOUT_FILENO)
		{
			dup2(fd2[1],STDOUT_FILENO);
			close(fd2[1]);
		}
		execl("./q4","q4",(char *)0);
	}
	return 0;
}
