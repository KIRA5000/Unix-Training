#include<stdio.h>
#include<pthread.h>
#include<sys/signal.h>
#include<string.h>
#include<stdlib.h>
extern char **environ;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int putenv_r(char *str)
{
	int flag=0;
	int j;
	char name[10];
	sigset_t nmask,omask;
	sigfillset(&nmask);
	pthread_sigmask(SIG_BLOCK,&nmask,&omask);
	for(int i=0;i<strlen(str);i++)
	{
		if(str[i]!='=')
		{
			continue;
		}
		else
		{
			strncpy(name,str,i);
			break;
		}
	}
	pthread_mutex_lock(&m);
	int i;
	for(i=0;environ[i]!=NULL;i++)
	{
		if((strncmp(name,environ[i],strlen(name))==0)&&(environ[i][strlen(name)]=='='))
		{
			printf("Hello\n");
			environ[i]=malloc(strlen(str));
			environ[i]=str;
			printf("Hello2\n");
			pthread_mutex_unlock(&m);
        		pthread_sigmask(SIG_SETMASK,&omask,NULL);
			return 0;
		}
	}
	environ[i]=malloc(sizeof(char *));
	environ[i]=str;
	environ[i+1]=NULL;
	pthread_mutex_unlock(&m);
	pthread_sigmask(SIG_SETMASK,&omask,NULL);
	return 0;
}
int main(void)
{
	char str[100];
	printf("Enter a string in format 'name=value'\n");
	scanf("%s",str);
	putenv_r(str);
	printf("%s\n",getenv("LOGNAME"));
	printf("%s\n",getenv("HELLO"));
	return 0;
}
