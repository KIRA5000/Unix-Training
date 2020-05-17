#include<stdio.h>
#include<time.h>
#include<sys/select.h>
int sleep_us(int ms)
{
	struct timeval tm;
	tm.tv_sec=ms/1000000;
	tm.tv_usec=ms%1000000;
	select(0,NULL,NULL,NULL,&tm);
}
int main(void)
{
	printf("Let's make the code sleep for 3 secs\n");
	sleep_us(3000000);
}
