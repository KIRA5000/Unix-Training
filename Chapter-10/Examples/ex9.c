#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
void intr(int signo)
{
	printf("Interrupt caught\n");
}
void chld(int signo)
{
	printf("Child caught\n");
}
int main(void)
{
	signal(SIGINT,intr);
	signal(SIGCHLD,chld);
	printf("%d\n",getpid());
	sleep(2);
	system("/bin/ed");
	printf("%d\n",getpgrp());
	return 0;
}
