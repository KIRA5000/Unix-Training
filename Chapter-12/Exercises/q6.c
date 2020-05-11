#include<stdio.h>
#include<pthread.h>
#include<sys/signal.h>
#include<unistd.h>
void alrm(int signo)
{
}
int slep(int sec)
{
	sigset_t nmask,omask;
	sigemptyset(&nmask);
	sigaddset(&nmask,SIGALRM);
	signal(SIGALRM,alrm);
	pthread_sigmask(SIG_BLOCK,&nmask,&omask);
	alarm(sec);
	int no,unslept;
	sigwait(&nmask,&no);
	unslept=alarm(0);
	pthread_sigmask(SIG_SETMASK,&omask,NULL);
	return unslept;
}
int main(void)
{
	int sec;
	printf("Enter the time until which you wanna sleep\n");
	scanf("%d",&sec);
	slep(sec);
}
