#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		printf("hello\n");
		_exit(1);
	}
	else
	{
		char cmd[100];
		sleep(1);
		sprintf(cmd,"ps p %i",pid);
                system(cmd);
	}
	return 0;
}
