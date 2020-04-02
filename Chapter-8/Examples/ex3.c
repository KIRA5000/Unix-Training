#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
int main(void)
{
	int pid=fork();
	if(pid==0)
	{
		printf("Hello i am child\n");
		_exit(5);
	}
	else
	{
		int statloc;
		wait(&statloc);
		printf("statloc:%d\n",statloc);
		if(WIFEXITED(statloc))
		{
			printf("exit status:%d\n",WEXITSTATUS(statloc));
		}
	}
	return 0;
}
