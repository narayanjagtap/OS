#include<stdio.h>
#include<stdlib.h>
#include"qadt.c"
//structure definition describing a process
typedef struct process
{
	int no,arrival,burst,depar,remain;
}process;

//function for fcfs sheduling
int fcfs(process *p,int pno)
{	
	int i;		
	p[0].depar=p[0].burst;
	for(i=0;i<pno;i++)
	{
		if(i!=0)		
			p[i].depar=p[i-1].depar+p[i].burst;
		else 
			printf("0 ");
		printf("p%d %d |",p[i].no,p[i].depar);
	}
	return 0;
}

//function for sjf non preamptive
int sjf_non(process p[],int pno)
{
	int t,flag[20]={0},i,j;
	t=p[0].depar=p[0].burst;
	flag[0]=1;
	printf("0 p%d %d | ",p[0].no,p[0].depar);
	for(i=1;i<pno;i++)
	{
		int minp,min=9999;
		for(j=1;j<pno;j++)
		{
			if((p[j].arrival<t)&& !flag[j])
			{
				if(p[j].burst<min)
				{
					min=p[j].burst;
					minp=j;
				}
			}
		}
		flag[minp]=i;
		p[minp].depar=t+p[minp].burst;
		t=p[minp].depar;
		printf("p%d %d | ",p[minp].no,p[minp].depar);
	}
	return 0;
}
//function to sort the processes  according to arrival(1) , acc to no(2)
int sort_process(process *p,int pno,int code)
{
	int i,j;
	for(i=0;i<pno-1;i++)
	{
		for(j=i+1;j<pno;j++)
		{
			if((code==1)?(p[i].arrival>p[j].arrival):(p[i].no>p[j].no))
			{
				process t=p[i];
				p[i]=p[j];
				p[j]=t;
			}//function for sjf preamptive
		}
	}
}


int disp(process p[],int pno)
{
	int avgtat=0,avgwt=0,i;
	for(i=0;i<pno;i++)
	{
		int tat=p[i].depar-p[i].arrival,wt=tat-p[i].burst;
		avgtat+=tat;
		avgwt+=wt;
		printf("\n%10d%5d%5d%5d%5d",i+1,p[i].arrival,p[i].burst,tat,wt);
	}
	printf("\nAvg tat is:%d\navg wt is:%d",avgtat/pno,avgwt/pno);
	return 0;
}
int round(process *p,int pno,int quanta)
{
	int count=0,current_time=0,t,flag[20]={0},i;
	queue x;
	process prev;
	x.f=x.r=-1;
	add(&x,0);
	flag[0]=1;
	prev.no=-1;
	while(!isempty(x))
	{
		t=del(&x);
		if(p[t].remain>quanta)
		{
			p[t].remain-=quanta;
			current_time+=quanta;
		}
		else
		{
			current_time+=p[t].remain;
			p[t].remain=0;
		}
		for(i=0;i<pno;i++)
		{
			if(!flag[i] && p[i].arrival<=current_time)
			{
				add(&x,i);
				flag[i]=1;
			}
		}
		if(p[t].remain)
			add(&x,t);
		if(prev.no!=p[t].no)
			printf("p%d %d | ",p[t].no,current_time);
		else
			printf("\b\b\b\b\b%d",current_time);
		p[t].depar=current_time;
		prev=p[t];
	}
	return 0;
}
//function to reinitialize p.remain
int reinit_remain(process *p,int pno)
{
	int i;
	for(i=0;i<pno;i++)
	{
		p[i].remain=p[i].burst;
	}
	return 0;
}
//function for sjf preamptive
int sjf_p(process *p,int pno)
{
	int current,flag[20]={0},prev,t,i;
	current=p[0].burst;prev=0;
	t=0;
	while(1)
	{
		int min1=9999,min,min2=9999,minn;
		for(i=0;i<pno;i++)
		{
			if(!flag[i])
			{
				if(((i!=t) && (p[i].burst+p[i].arrival)<current))
				{
					if(min1>p[i].burst)
					{
						min=i;
						min1=p[i].burst;
						break;
					}
				}
				if((i!=t) && p[i].arrival <current)
				{
					if(min2>p[i].burst)
					{
						minn=i;
						min2=p[i].burst;
					}				
				}
			}
			else if(flag[i]==1)
			{

				if(min2>p[i].remain)
				{
					minn=i;
					min2=p[i].remain;
				}					
			}								
		}
		/*printf("\n%d..",min1);
		printf("%d..",min2);	
		printf("%d\n",minn);*/
		if(min1==9999 && min2==9999)
			break;
		if(min1==9999)
		{
			flag[t]=2;
			prev=current;
			p[t].depar=current;
			printf("p%d %d ",p[t].no,current);
			t=minn;
			current+=(flag[t]?p[t].remain:p[t].burst);
		}
		else
		{
			flag[t]=1;
			p[t].remain=current-p[min].arrival;
			current=prev=p[min].arrival;
			printf(" p%d %d",p[t].no,current);
			current+=p[min].burst;
			t=min;
		}
//printf("\nprev==%d current=%d selected =%d\n",prev,current,t+1);		
	}
}
//the main function
int main()
{
	int pno,i,j,ch;
	process p[20],q[20];
	printf("\nEnter no of processes:");
	scanf("%d",&pno);
	for(i=0;i<pno;i++)
	{
		p[i].no=i+1;
		printf("\nEnter arrival time for process %d:",i+1);
		scanf("%d",&p[i].arrival);
		printf("\nEnter Burst time for process %d:",i+1);
		scanf("%d",&p[i].burst);
		p[i].remain=p[i].burst;
		q[i]=p[i];
	}
	while(1)
	{
	printf("\n>>>>>>>>>>>>>>>>>>>MENU<<<<<<<<<<<<<<<<<<<<<<<<\
	\n1.FCFS\
	\n2.SJF NONPREAMPTIVE\
	\n3.SJF PREAMPTIVE\
	\n4.RR\
	\n5.Exit\
	\nEnter choice :");
	scanf("%d",&ch);
	switch(ch)
	{	
		case 1://fcfs
			sort_process(p,pno,1);
			fcfs(p,pno);
			sort_process(p,pno,2);
			printf("\n\n%10s%5s%5s%5s%5s","PROCESS","A.T","B.T","TAT","WT");
			disp(p,pno);
			break;
		case 2://sjf non
			sort_process(p,pno,1);
			sjf_non(p,pno);
			sort_process(p,pno,2);
			printf("\n\n%10s%5s%5s%5s%5s","PROCESS","A.T","B.T","TAT","WT");
			disp(p,pno);
			break;
		case 3://sjf preamp
			sort_process(p,pno,1);
			//reinit_remain(p,pno);
			sjf_p(p,pno);
			printf("\n\n%10s%5s%5s%5s%5s","PROCESS","A.T","B.T","TAT","WT");
			sort_process(p,pno,2);
			disp(p,pno);
			break;
		case 4://round robin
			sort_process(q,pno,1);
			round(q,pno,4);	
			printf("\n\n%10s%5s%5s%5s%5s","PROCESS","A.T","B.T","TAT","WT");
			sort_process(q,pno,2);
			disp(q,pno);
			break;	
		case 5:exit(0);
		default:printf("\nInvalid choice.....");
	}	//switch
	}
		return 0;


}
