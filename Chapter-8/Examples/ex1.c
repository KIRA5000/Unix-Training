#include<stdio.h>
#include<unistd.h>
int gvar=10;
int main(void)
{
	int lvar=20;
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		lvar++;
		gvar++;
	}
	else
	{
		sleep(2);
	}
	printf("lvar:%d gvar:%d\n",lvar,gvar);
	return 0;
}
