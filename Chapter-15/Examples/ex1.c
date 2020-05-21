#include<stdio.h>
#include<unistd.h>
int main(void)
{
	pid_t pid;
	int fd[2];
	pipe(fd);
	pid=fork();
	if(pid==0)
	{
		close(fd[0]);
		write(fd[1],"This is child",16);
	}
	else
	{
		close(fd[1]);
		printf("Parent Started\n");
		char buff[16];
		read(fd[0],buff,16);
		printf("%s\n",buff);
	}
	return 0;
}
