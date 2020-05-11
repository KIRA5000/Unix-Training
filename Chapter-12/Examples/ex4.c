#include<stdio.h>
#include<pthread.h>
#include<string.h>
extern char **environ;
pthread_once_t ponce=PTHREAD_ONCE_INIT;
pthread_mutex_t m;
void once()
{
	pthread_mutexattr_t mattr;
	pthread_mutexattr_init(&mattr);
	pthread_mutexattr_settype(&mattr,PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&m,&mattr);
	pthread_mutexattr_destroy(&mattr);
}
void getenv_r(char *name,char *buff,int buffsize)
{
	pthread_once(&ponce,once);
	printf("%ld\n",strlen(name));
	pthread_mutex_lock(&m);
	for(int i=0;environ[i]!=NULL;i++)
	{
		if((strncmp(name,environ[i],strlen(name))==0)&&(environ[i][strlen(name)]=='='))
		{
			printf("%s %c  %s\n",name,environ[i][strlen(name)],environ[i]);
			strncpy(buff,&environ[i][strlen(name)+1],buffsize);
		}
	}
	pthread_mutex_unlock(&m);
}
int main(void)
{
	char name[6];
	printf("Enter the name whose value you want to know\n");
	scanf("%s",name);
	char buff[100];
	getenv_r(name,buff,100);
	printf("%s: %s\n",name,buff);
/*	if(m!=NULL)
	{
		printf("Deleting mutex\n");
		pthread_mutex_destroy(&m);
	}*/
	return 0;
}
