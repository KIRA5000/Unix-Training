#include<stdio.h>
#include<unistd.h>
int main(void)
{
	char str1[]="This is child\n";
	char str2[]="This is parent\n";
	pid_t pid=fork();
	setbuf(stdout,NULL);
	if(pid==0)
	{
		for(int i=0;i<sizeof(str1);i++)
                {
                        putc(str1[i],stdout);
                }

	}
	else
	{
		for(int i=0;i<sizeof(str2);i++)
                {
                        putc(str2[i],stdout);
                }

	}
	return 0;
}
