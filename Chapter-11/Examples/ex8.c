#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
int main(int argc,int argv)
{
	int fd;
	struct stat st;
	struct timespec times[2];
		stat("/home/kira5000/Desktop/Unix-Training/Chapter-11/Examples/hello.txt",&st);
		times[0]=st.st_atim;
		times[1]=st.st_mtim;
		printf("Time before opening:%ld %ld\n",st.st_atim.tv_sec,st.st_mtim.tv_sec);
		sleep(3);
		fd=open("/home/kira5000/Desktop/Unix-Training/Chapter-11/Examples/hello.txt",O_RDWR|O_APPEND);
		stat("/home/kira5000/Desktop/Unix-Training/Chapter-11/Examples/hello.txt",&st);
		printf("Time after opening:%ld %ld\n",st.st_atim.tv_sec,st.st_mtim.tv_sec);
		write(fd,"Hello\n",10);
		sleep(3);
		stat("/home/kira5000/Desktop/Unix-Training/Chapter-11/Examples/hello.txt",&st);
                printf("Time after writing:%ld %ld\n",st.st_atim.tv_sec,st.st_mtim.tv_sec);
		futimens(fd,times);
		stat("/home/kira5000/Desktop/Unix-Training/Chapter-11/Examples/hello.txt",&st);
                printf("Time after futimens:%ld %ld\n",st.st_atim.tv_sec,st.st_mtim.tv_sec);
	return 0;
}
