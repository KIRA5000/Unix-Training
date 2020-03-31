#include<stdio.h>
#include<unistd.h>
int gvar=10;
int main(void)
{
	int lvar=20;
	pid_t pid;
	pid=vfork();
	if(pid==0)
	{
		lvar++;
		gvar++;
		_exit(0);  //doesn't flush std i/o
	}
	else
	{
		printf("lvar:%d gvar:%d\n",lvar,gvar);
	}
	return 0;
}
