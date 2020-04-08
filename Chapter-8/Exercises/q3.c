#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(void)
{
	pid_t pid;
	pid=fork();
	siginfo_t info;
	int flags = WCONTINUED|WEXITED|WSTOPPED;
	if(pid==0)
	{
		exit(7);
	}
	else
	{
		waitid(P_PID,pid,&info,flags);
		if(info.si_code==CLD_EXITED)
			printf("Normal termination, status=%d\n",info.si_status);
	}
	pid=fork();
        if(pid==0)
        {
                abort();
        }
        else
        {
                waitid(P_PID,pid,&info,flags);
                if(info.si_code==CLD_EXITED)
                        printf("Normal termination, status=%d\n",info.si_status);
		else if(info.si_code==CLD_DUMPED)
			printf("Abnormal termination, status=%d\n",info.si_status);
        }
	pid=fork();
	int i;
        if(pid==0)
        {
               i=10/0;
        }
        else
        {
                waitid(P_PID,pid,&info,flags);
                if(info.si_code==CLD_EXITED)
                        printf("Normal termination, status=%d\n",info.si_status);
                else if(info.si_code==CLD_DUMPED)
                        printf("Abnormal termination, status=%d\n",info.si_status);
	}
	return 0;
}
