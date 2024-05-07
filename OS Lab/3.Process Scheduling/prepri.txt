#include<stdio.h>
#include<conio.h>
#include<graphics.h>


struct pri
{
	int at,bt,prior,flag;
	int no,tat,toc,wt;
};

void sort(struct pri ready[],int front,int rear)
{
	int i,j;
	struct pri temp;
	for(i=front-1;i<rear;i++)
	{
		for(j=front;j<rear;j++)
		{
			if(ready[i].prior > ready[j].prior)
			{
				temp=ready[i];
				ready[i]=ready[j];
				ready[j]=temp;
			}
		}
	}
}

void priority()
{
	int k,tt=1000,tbt=0,i,j,kk,n,tempt,front=0,rear=-1,x,y;
	struct pri p[20],ready[20];
	char *buffer;
	printf("\nEnter how many processes::");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		printf("\nProcess %d",i+1);
		printf("\nArrival time::");
		scanf("%d",&p[i].at);
		printf("\nBurst time::");
		scanf("%d",&p[i].bt);
		printf("\nPriority::");
		scanf("%d",&p[i].prior);
		p[i].no=i+1;
		p[i].flag=0;
		tbt=tbt+p[i].bt;
		if(tt>p[i].at)
			tt=p[i].at;
	}
	tempt=tt;
	k=0;
	kk=0;
	while(tt<tbt)
	{
		k=0;
		for(i=0;i<n;i++)
		{
			if(p[i].at==tt && p[i].flag==0)
			{
				ready[++rear]=p[i];
				p[i].flag=1;
				k=1;
			}
		}
		if(k==1)
		{
			sort(ready,front,rear);
			if(kk>=tt)
			{
				kk=kk+ready[front].bt;
				front++;
			}

		}
		else
		{
			if(kk==tt)
			{
				kk=kk+ready[front].bt;
				front++;
			}
		}
	  tt++;
	}

/*	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(p[i].at>p[i].at)
			{
			   temp=p[i];
			   p[i]=p[i+1];
			   p[i+1]=temp;
			}
		}
	} */
	cleardevice();
	x=25;
	y=50;
	for(i=0;i<n;i++)
	{
		rectangle(x,y,x+(10*ready[i].bt),y+30);
		sprintf(buffer,"%d",ready[i].no);
		outtextxy(x+(10*ready[i].bt)/2,y+15,buffer);
		sprintf(buffer,"%d",tempt);
		outtextxy(x-5,y+35,buffer);
		x+=10*ready[i].bt;
		tempt+=ready[i].bt;


	}
		sprintf(buffer,"%d",tempt);
		outtextxy(x-5,y+35,buffer);



}

void main()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"");
	priority();

	getch();
	closegraph();

}