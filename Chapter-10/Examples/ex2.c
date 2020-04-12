#include<stdio.h>
#include<setjmp.h>
jmp_buf env;
void jump();
int main(void)
{
	if(setjmp(env)==0)
		jump();
	printf("Main return complete\n");
	return 0;
}
void jump()
{
	int y;
	printf("Do you wanna jump to main()?(0/1)\n");
	scanf("%d",&y);
	if(y==1)
	{
		longjmp(env,1);
	}
	printf("No jump performed, normally unwinding the stack\n");
}
