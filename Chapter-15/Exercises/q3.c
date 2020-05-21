#include<stdio.h>
#include<unistd.h>
#include<errno.h>
int main(void)
{
	FILE *in=popen("hello","r");
	if(in==NULL)
	{
		perror("poper error");
	}
	else
	{
		char cmd[100];
		while(fgets(cmd,100,in)!=NULL)
		{
			write(STDIN_FILENO,cmd,100);
		}
	}
	return 0;
}
