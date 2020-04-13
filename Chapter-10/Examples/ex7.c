#include<stdio.h>
#include<signal.h>
#include<setjmp.h>
#include<unistd.h>
jmp_buf env;
void func(int signo)
{
	printf("SIGUSR signal handled\n");
	sleep(2);
	siglongjmp(env,1);
}
int main(void)
{
	struct sigaction act,oact;
	act.sa_handler=func;
	act.sa_flags=0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGQUIT,&act,&oact);
	if(sigsetjmp(env,1)==0)
		while(1);
	sleep(4);
	sigset_t evc;
	sigpending(&evc);
	printf("%d\n",sigismember(&evc,SIGQUIT));
	printf("Main returned\n");
	return 0;
}
