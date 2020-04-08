#include<stdio.h>
#include<unistd.h>
int sum(int a,int b)
{
	pid_t pid = fork();
	if(pid==0)
	{
		a++;
		b++;
	}
	return a+b;
}
int main(void)
{
	int a=sum(4,5);
	printf("a:%i\n",a);
	return 0;
}
