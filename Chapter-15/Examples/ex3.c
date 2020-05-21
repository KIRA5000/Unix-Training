#include<stdio.h>
#include<unistd.h>
#include<ctype.h>
int main(void)
{
	char c;
	while((c=getchar())!=EOF)
	{
		if((c>=65)&&(c<=90))
		{
			c+=32;
			//putchar(c);
			//printf("%c\n",c);
		}
		putchar(c);
		if(c=='\n')
                {
                        fflush(stdout);
                }

	}
	return 0;
}
