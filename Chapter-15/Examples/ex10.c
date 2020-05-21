#include<stdio.h>
#include<string.h>
#include<sys/shm.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
int main()
{
	key_t key=ftok("/home/kira5000/Desktop/hello1.txt",1);
	int shmid=shmget(key,6,0666);
	void *mem=shmat(shmid,NULL,SHM_RDONLY);
	char str[6];
	memcpy(str,(char *)mem,6);
	printf("The string is:%s\n",str);
	shmdt(mem);
	return 0;
}
