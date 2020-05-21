#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<errno.h>
#include<stdlib.h>
struct msg_t
{
	int type;
	char data[200];
};
int main(void)
{
	key_t key;
	key=ftok("/home/kira5000/Desktop/hello1.txt",1);
	int msgid;
	//perror("ftok");
	msgid=msgget(key,0666|IPC_CREAT);
	//perror("msgid");
	struct msg_t msg;
	while(1)
	{
		if(msgrcv(msgid,&msg,sizeof(msg),0,0)!=-1)
		{
			printf("%s",msg.data);
		}
		else
		{
			perror("msgrcv");
			exit(1);
		}
	}
	return 0;
}
