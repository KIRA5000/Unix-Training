#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<errno.h>
#include<unistd.h>
#include<sys/socket.h>
#include<string.h>
#define MAXSLEEP 128
int connect_retry(int domain,int type,int protocol,struct sockaddr *addr,socklen_t alen)
{
	int sockfd;
	for(int i=1;i<=MAXSLEEP;i<<=1)
	{
		if((sockfd=socket(domain,type,protocol))<0)
		{
			perror("socket");
			exit(1);
		}
		if(connect(sockfd,addr,alen)==0)
		{
			return sockfd;
		}
		close(sockfd);
		if(i<=MAXSLEEP/2)
		{
			sleep(i);
		}
	}
	return -1;
}
void print_uptime(int sockfd)
{
	int n;
	char buff[128];
	while((n=recv(sockfd,buff,128,0))>0)
	{
		write(STDOUT_FILENO,buff,n);
		if(n<0)
		{
			perror("recv");
			exit(1);
		}
	}
}
int main(int argc,char *argv[])
{
	struct addrinfo hint,*alist,*aip;
	int err;
	int sockfd;
	if(argc!=2)
	{
		printf("usage: ./a.out hostname");
		exit(1);
	}
	else
	{
		memset(&hint,0,sizeof(hint));
		hint.ai_socktype=SOCK_STREAM;
		hint.ai_canonname=NULL;
		hint.ai_addr=NULL;
		hint.ai_next=NULL;
		if((err=getaddrinfo(argv[1],"ruptime",&hint,&alist))!=0)
		{
			printf("Error:%s\n",gai_strerror(err));
			exit(err);
		}
		else
		{
			for(aip=alist;aip!=NULL;aip=aip->ai_next)
			{
				if((sockfd=connect_retry(aip->ai_family,SOCK_STREAM,0,aip->ai_addr,aip->ai_addrlen))<0)
				{
					perror("connect");
				}
				else
				{
					print_uptime(sockfd);
				}
			}
		}
		return 0;
	}
}
