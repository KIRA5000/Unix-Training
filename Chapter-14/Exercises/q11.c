#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<string.h>
int main(int argc,char *argv[])
{
	int fd1,fd2;
	struct stat st;
	off_t off=0;
	int len;
	if(argc!=3)
	{
		printf("./a.out <file1> <file2>\n");
		exit(1);
	}
	else
	{
		fd1=open(argv[1],O_RDONLY);
		fd2=open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0755);
		fstat(fd1,&st);
		ftruncate(fd2,st.st_size);
		int i=0;
		while(i==0)
		{
			void *adr1,*adr2;
			if((st.st_size-off)>1024)
			{
				len=1024;
			}
			else
			{
				len=st.st_size-off;
			}
			adr1=mmap(0,len,PROT_READ,MAP_SHARED,fd1,off);
			if(i==0)
			{
				close(fd1);
				i++;
			}
			adr2=mmap(0,len,PROT_WRITE,MAP_SHARED,fd2,off);
			memcpy(adr2,adr1,len);
			munmap(adr1,len);
			munmap(adr2,len);
			off+=len;
		}
	}
	return 0;
}
