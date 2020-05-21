#include<stdio.h>
#include<sys/msg.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<string.h>
#include<errno.h>
struct msg_t
{
	int mtype;
	char data[200];
};
int main(void)
{
	struct msqid_ds buf;
	key_t key;
	key=ftok("/home/kira5000/Desktop/hello1.txt",1);
	//perror("ftok");
	int msgid;
	msgid=msgget(key,0666|IPC_CREAT);
	//perror("msgget");
	struct msg_t msg;
	msg.mtype=1;
	int n;
	while(fgets(msg.data,200,stdin)!=NULL)
	{
		msgsnd(msgid,&msg,sizeof(msg),0);
		//perror("msgsnd");
	}
	msgctl(msgid,IPC_RMID,&buf);
	return 0;
}
