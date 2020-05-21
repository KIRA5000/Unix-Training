#include<stdio.h>
#include<fcntl.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	key_t key;
	key=ftok("/home/kira5000/Desktop/hello1.txt",1);
	int shmid=shmget(key,6,0666|IPC_CREAT);
	if(shmid<0)
	{
		printf("Shared memory creation failed\n");
		shmid=shmget(key,6,0666);
		if(shmid<0)
		{
			printf("Shared memory failed\n");
			exit(1);
		}
	}
	void *mem;
	mem=shmat(shmid,NULL,0);
	memset((char *)mem,'\0',6);
	memcpy((char *)mem,"hello",6);
	shmdt(mem);
	return 0;
}
