#include<stdio.h>
#include<unistd.h>
int main(int argc,char **argv)
{
	for(int i=0;i<argc;i++)
	{
		printf("%d: %s\n",i+1,argv[i]);
	}
	extern char **environ;
	for(char **ptr=environ;*ptr!=0;ptr++)
	{
		printf("%s\n",*ptr);
	}
	return 0;
}
