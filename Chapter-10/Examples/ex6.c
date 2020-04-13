#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void squit()
{
	printf("Quit signal caught\n");
}
int main(void)
{
	signal(SIGQUIT,squit);
	sigset_t nset,oset,pmask;
	sigemptyset(&nset);
	sigaddset(&nset,SIGQUIT);
	sigprocmask(SIG_BLOCK,&nset,&oset);
	sleep(5);
	sigpending(&pmask);
	if(sigismember(&pmask,SIGQUIT))
	{
		printf("SIGQUIT pending\n");
	}
	sigprocmask(SIG_SETMASK,&oset,NULL);
	sleep(2);
	printf("SIGQUIT released\n");
	return 0;
}
