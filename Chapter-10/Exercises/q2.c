#include<stdio.h>
#include<signal.h>
#include<string.h>
int sig2str(int signo,char *name)
{
	if(signo<0||signo>NSIG)
		return -1;
	else
	{
		strcpy(name,strsignal(signo));
	}

}
int main(void)
{
	int signo;
	printf("Enter the signal number\n");
	scanf("%d",&signo);
	char name[20];
	sig2str(signo,name);
	printf("Name of signal is:%s\n",name);
	return 0;
}
