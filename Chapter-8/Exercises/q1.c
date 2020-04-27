#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int gvar=20;
int main(void)
{
	int lvar=10;
	printf("Hello there");
	pid_t pid=vfork();
	//printf("Hello there");
	if(pid==0)
	{
		lvar++;
		gvar++;
		fclose(stdout);
		exit(0);
	}
	printf("lvar:%i gvar:%i\n",lvar,gvar);
	return 0;
}
