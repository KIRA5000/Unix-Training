#include<stdio.h>
#include<signal.h>
void handle(int signo)
{
	if(signo==SIGUSR1)
		printf("User Exception recieved\n");
}
int main(void)
{
	signal(SIGUSR1,handle);
	signal(SIGTERM,SIG_IGN);
	while(1);
	return 0;
}
