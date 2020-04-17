#include<stdio.h>
#include<signal.h>
#include<unistd.h>
void usr(int signo)
{
	if(signo==SIGUSR1)
		printf("SIGUSR1\n");
	else
		printf("SIGUSR2\n");
}
int main(void)
{
	signal(SIGUSR1,usr);
	signal(SIGUSR2,usr);
	//for(;;)
		pause();
	return 0;
}
