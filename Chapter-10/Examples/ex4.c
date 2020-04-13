#include<stdio.h>
#include<unistd.h>
#include<signal.h>
void alrm()
{
	//signal(SIGALRM,alrm);
	printf("alarm caught\n");
}
int main(void)
{
	signal(SIGALRM,alrm);
	alarm(10);
	printf("%d\n",pause());
	printf("%d\n",alarm(3));
	pause();
	return 0;
}
