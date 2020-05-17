#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#define LOCKFILE "/home/kira5000/Desktop/hello.txt"
int lock_set(int type, int whence, int start, int length, int fd)
{
	struct flock lk;
	lk.l_type=type;
	lk.l_whence=whence;
	lk.l_start=start;
	lk.l_len=length;
	lk.l_pid=getpid();
	return fcntl(fd,F_SETLK,&lk);
}
struct flock *lock_get(int type, int whence, int start, int length, int fd)
{
	struct flock lk;
	lk.l_type=type;
        lk.l_whence=whence;
        lk.l_start=start;
        lk.l_len=length;
	//perror("before fcntl");
	printf("%d\n",fcntl(fd,F_GETLK,&lk));
	//perror("fcntl");
	if(lk.l_type==F_UNLCK)
	{
		printf("Sucessfull\n");
	}
}
int main(void)
{
	printf("%d\n",F_GETLK);
	struct flock lk;
	int fd=open(LOCKFILE,O_RDWR|O_CREAT|O_TRUNC,0755);
	lock_set(F_WRLCK,SEEK_SET,0,0,fd);
	printf("Let's check if lock has been set or not:\n");
	lock_get(F_WRLCK,SEEK_SET,0,0,fd);
	/*if(lk.l_type==F_WRLCK)
	{
		printf("Write lock successfull\n");
	}
	else
	{
		printf("Lock not successfull\n");
	}*/
	lock_set(F_UNLCK,SEEK_SET,0,0,fd);
	return 0;
}
