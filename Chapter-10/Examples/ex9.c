#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
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
	system("/bin/ed");
	return 0;
}
