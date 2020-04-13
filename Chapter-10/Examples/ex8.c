#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void sig()
{
	printf("Quit handled\n");
}
void sig2()
{
        printf("Interupt handled\n");
}
int main(void)
{
	signal(SIGQUIT,sig);
	signal(SIGINT,sig2);
	sigset_t nmask,omask,nmask2;
	sigemptyset(&nmask);
	sigemptyset(&nmask2);
	sigaddset(&nmask,SIGQUIT);
	sigaddset(&nmask,SIGINT);
	sigaddset(&nmask2,SIGINT);
	sigprocmask(SIG_BLOCK,&nmask,&omask);
	printf("Here in critical section\n");
	sleep(10);
	sigpending(&nmask2);
	sigprocmask(SIG_SETMASK,&omask,NULL);
	printf("End of main\n");
	return 0;
}
