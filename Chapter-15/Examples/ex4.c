#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#define ex3 "/home/kira5000/Desktop/Unix-Training/Chapter-15/Examples/ex3"
int main(void)
{
	FILE *fdin;
	char line[100];
	if((fdin=popen(ex3,"r"))==NULL)
	{
		printf("popen error\n");
		exit(127);
	}
	while(1)
	{
		char c;
		fputs("prompt> ",stdout);
		fflush(stdout);
		//perror("before if");
		if(fgets(line,100,fdin)==NULL)
		{
			break;
		}
		else
		{
			fputs(line,stdout);
		}
	}
	pclose(fdin);
	return 0;
}
