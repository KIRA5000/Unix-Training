#include<stdio.h>
#include<string.h>
extern char **environ;
char *geten(char *name)
{
	char ret[50];
	int t;
	for(int i=0;environ[i]!=0;i++)
	{
		if((strncmp(name,environ[i],strlen(name))==0)&&(environ[i][strlen(name)]=='='))
		{
			printf("%s \n",environ[i]);
			t=i;
			break;
		}
	}
	return &environ[t][strlen(name)+1];
}
int main(void)
{
	char name[20];
	char *ret;
	printf("Enter variable value that you wanna find\n");
	scanf("%s",name);
	ret=geten(name);
	printf("%s: %s\n",name,ret);
	return 0;
}
