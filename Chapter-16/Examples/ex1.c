#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
print_flags(struct addrinfo *aip)
{
	printf("flags:");
	if((aip->ai_flags)==0)
	{
		printf("0\n");
	}
	else
	{
		if (aip->ai_flags & AI_PASSIVE)
		printf(" passive");
		if (aip->ai_flags & AI_CANONNAME)
		printf(" canon");
		if (aip->ai_flags & AI_NUMERICHOST)
		printf(" numhost");
		if (aip->ai_flags & AI_NUMERICSERV)
		printf(" numserv");
		if (aip->ai_flags & AI_V4MAPPED)
		printf(" v4mapped");
		if (aip->ai_flags & AI_ALL)
		printf(" all");
		printf("\n");
	}
}
void print_family(struct addrinfo *aip)
{
	printf(" family ");
	switch (aip->ai_family) 
	{
		case AF_INET:
			printf("inet");
			break;
		case AF_INET6:
			printf("inet6");
			break;
		case AF_UNIX:
			printf("unix");
			break;
		case AF_UNSPEC:
			printf("unspecified");
			break;
		default:
			printf("unknown");
	}
	printf("\n");
}
void print_type(struct addrinfo *aip)
{
	printf(" type ");
	switch (aip->ai_socktype) 
	{
		case SOCK_STREAM:
			printf("stream");
			break;
		case SOCK_DGRAM:
			printf("datagram");
			break;
		case SOCK_SEQPACKET:
			printf("seqpacket");
			break;
		case SOCK_RAW:
			printf("raw");
			break;
		default:
		printf("unknown (%d)", aip->ai_socktype);
	}
	printf("\n");
}
void print_protocol(struct addrinfo *aip)
{
	printf(" protocol ");
	switch (aip->ai_protocol) 
	{
		case 0:
			printf("default");
			break;
		case IPPROTO_TCP:
			printf("TCP");
			break;
		case IPPROTO_UDP:
			printf("UDP");
			break;
		case IPPROTO_RAW:
			printf("raw");
			break;
		default:
			printf("unknown (%d)", aip->ai_protocol);
	}
	printf("\n");
}
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("./a.out <hostname> <service>\n");
		exit(1);
	}
	else
	{
		struct addrinfo hint,*alist,*aip;
		hint.ai_flags=AI_CANONNAME;
		hint.ai_family=0;
		hint.ai_socktype=0;
		hint.ai_protocol=0;
		hint.ai_addrlen = 0;
		hint.ai_canonname = NULL;
		hint.ai_addr = NULL;
		hint.ai_next = NULL;
		int ret;
		if((ret=getaddrinfo(argv[1],argv[2],&hint,&alist))!=0)
		{
			printf("Error:%s\n",gai_strerror(ret));
		}
		else
		{
			for(aip=alist;aip!=NULL;aip=aip->ai_next)
			{
				print_flags(aip);
				print_family(aip);
				print_type(aip);
				print_protocol(aip);
			}
		}
		printf("Adress:%s\n",(char *)alist->ai_addr);
		return 0;
	}
}
