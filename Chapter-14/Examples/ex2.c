#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(void)
{
	int fd;
	fd = open("/home/kira5000/Desktop/hello.txt",O_RDWR|O_CREAT|O_APPEND,0755);
	for(int i=0;i<50000000;i++)
	{
		write(fd,"a",1);
	}
	return 0;
}
