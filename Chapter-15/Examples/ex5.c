#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(void)
{
	int n;
	char line[100];
	int i1,i2;
	while((n=read(STDIN_FILENO,line,100))>0)
	{
		line[n]=0;
		if(sscanf(line,"%d%d",&i1,&i2)==2)
		{
			sprintf(line,"%d\n",i1+i2);
			n=strlen(line);
			write(STDOUT_FILENO,line,n);
		}
	}
	return 0;
}
