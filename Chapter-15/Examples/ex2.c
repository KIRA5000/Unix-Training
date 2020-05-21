#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#define PAGER "${PAGER:-more}"
int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("./a.out <filename>\n");
		exit(1);
	}
	char buff[1024];
	FILE* fdout;
	FILE* fdin=fopen(argv[1],"r");
	fdout=popen(PAGER,"w");
	while(fgets(buff,1024,fdin)!=NULL)
	{
		fputs(buff,fdout);
	}
	fclose(fdin);
	pclose(fdout);
	return 0;
}
