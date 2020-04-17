#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
void sig_alr(int signo)
{
	static int i=1;
	printf("Alarm %d caught\n",i++);
}
struct node
{
	unsigned int sec;
	struct node *next;
};
struct node *head=NULL;
struct node *tail=NULL;
void push(unsigned int sec)
{
	if(head==NULL)
	{
		head=(struct node*)malloc(sizeof(struct node));
		head->sec=sec;
		head->next=NULL;
		tail=head;
	}
	else
	{
		struct node *ndata=(struct node *)malloc(sizeof(struct node));
		ndata->sec=sec;
		ndata->next=NULL;
		tail->next=ndata;
		tail=ndata;
	}
}
void alrm()
{
	struct node *curr=head;
	head=head->next;
	alarm(curr->sec);
	pause();
}
int main(void)
{
	signal(SIGALRM,sig_alr);
	unsigned int sec;
	int choice=1;
	while(choice)
	{
		printf("Enter seconds for alarm\n");
		scanf("%d",&sec);
		push(sec);
		printf("Do you wanna increase alarm queue?\n");
		scanf(" %d",&choice);
	}
	printf("Starting alarm sequence\n");
	while(head!=NULL)
	{
		alrm();
	}
	return 0;
}
