#include<stdio.h>
#include<setjmp.h>
jmp_buf env;
void jump()
{
	longjmp(env,1);
}
int main(void)
{
	int avar=1;
	register int rvar=2;
	static int svar=3;
	volatile int vvar=4;
	if(setjmp(env)!=0)
		printf("auto:%d register:%d static:%d volatile:%d\n",avar,rvar,svar,vvar);
	else
	{
		avar++;
		rvar++;
		svar++;
		vvar++;
		jump();
	}
	return 0;
}
