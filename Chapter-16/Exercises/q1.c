#include<unistd.h>
#include<stdio.h>
#include<arpa/inet.h>
int main(void)
{
	uint16_t a=123;
	uint16_t b;
	b=htons(a);
	if(a==b)
	{
		printf("Big Endian\n");
	}
	else
	{
		printf("Small Endian\n");
	}
	b=ntohs(a);
        if(a!=b)
        {
                printf("Big Endian\n");
        }
        else
        {
                printf("Small Endian\n");
        }
	return 0;
}
