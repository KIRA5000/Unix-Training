#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
char buf[50000000];
void clear_fl(int fd,int flag)
{
	int val;
	val=fcntl(fd,F_GETFL,0);
	val&=~flag;
	fcntl(fd,F_SETFL,val);
}
void set_fl(int fd,int flag)
{
	int val;
	val=fcntl(fd,F_GETFL,0);
	val|=flag;
	fcntl(fd,F_SETFL,val);
}
int main(void)
{
	char *ptr;
	int ntowr,nwr;
	ntowr=read(STDIN_FILENO,buf,sizeof(buf));
	fprintf(stderr,"size:%d read from file\n",ntowr);
	set_fl(STDOUT_FILENO,O_NONBLOCK);
	ptr=buf;
	while(ntowr>0)
	{
		errno=0;
		nwr=write(STDOUT_FILENO,buf,ntowr);
		fprintf(stderr,"writen:%d errno:%d\n",nwr,errno);
		if(nwr>0)
		{
			ntowr-=nwr;
			ptr+=nwr;
		}
	}
	clear_fl(STDOUT_FILENO,O_NONBLOCK);
	return 0;
}
