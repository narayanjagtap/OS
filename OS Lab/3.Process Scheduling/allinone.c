//HEADER FILES
#include<stdio.h>
#include<stdlib.h>

//STRUCTURE FOR PROCESS
typedef struct process
{
	int pid,arr,bur,rem,tat,wt,fg,act,pri;
}process;

//STRUCTURE FOR QUEUE
typedef struct queue
{
 process p;
 struct queue *next;
}queue;

//PROCEDURE TO INSERT AN ELEMENT OF TYPE PROCESS INTO THE QUEUE
void add(queue **f,queue **r,process pr)
{
	queue *nev;
	nev=(queue*)malloc(sizeof(queue));
	nev->p=pr;
	nev->next=NULL;
	if((*f)==NULL)
		(*f)=(*r)=nev;
	else
	{
		(*r)->next=nev;
		(*r)=nev;
	}
}

//FUNCTION TO DELETE AN ELEMENT FROM THE QUEUE
process del(queue **f,queue **r)
{
	queue *nev;
	process temp;

	if((*f)==NULL)
		printf("");
	else
	{
		nev=(*f);
		if((*f)==(*r))
		   (*f)=(*r)=NULL;
		else
		   (*f)=(*f)->next;
		temp=nev->p;
		free(nev);
	}
	return temp;
}

//FUNCTION PROTOTYPING
void fcfs(int,process[10]);
void sjfnp(int,process[10]);
void sjfp(int,process[10]);
void rr(int,process[10]);
//void prinp(int,process[10]);
//void prip(int,process[10]);
void sort1(int,process[10]);
void sort2(int,process[10]);
void display(int,process[10]);

//MAIN FUNCTION
int main()
{
	process p[10];
	int i,pr,ch,op;
	char ch1;
	printf("\n---- CPU SCHEDULING ----");
        printf("\n Enter Number of Processes :");
	scanf("%d",&pr);
        for(i=1;i<=pr;i++)
	{
		        p[i].pid=i;
		        printf("\n Enter Details for Process %d:",i);	  
			printf("\n Arrival Time:");
		        scanf("%d",&p[i].arr);
			printf(" Burst Time:");
		        scanf("%d",&p[i].bur);
			p[i].rem=p[i].bur;
			p[i].act=p[i].tat=p[i].wt=0;
	}
      	do
      	{
	 printf("\n---CPU SCHEDULING ALGORITHMS---");
	 printf("\n  1.] FCFS(First Come First Serve)");
	 printf("\n  2.] SJF(Shortest Job First)");
	 printf("\n  3.] RR(Round Robin)");
	 printf("\n  4.] PRIORITY");
	 printf("\n  5.] Exit");
	 printf("\n  Enter Choice:");
	 scanf("%d",&ch);
	 switch(ch)
	 {
		case 1:
			{
			  fcfs(pr,p);
			  break;
			}
		case 2:
			{
			  printf("\n 1.] SJF Non-Preemptive");
			  printf("\n 2.] SJF Preemptive");
			  printf("\n Enter Option:");
			  scanf("%d",&op);
			  if(op==1)
			  {
				sjfnp(pr,p);
			  }
			  else if(op==2)
			  {
				sjfp(pr,p);
			  }
			  else
			  {
				printf("\n Not a Valid Option");
			  }
			   break;
			 }
		case 3:
			 {
			   	rr(pr,p);
			   	break;
			 }
		case 4:
			{
			  int i,pri;
			  for(i=1;i<=pr;i++)
    			  {
				printf("\n Enter Priority for Process%d :",i);
				scanf("%d",&pri);
        			p[i].pri=pri;
			  }
			  printf("\n 1.] Priority Non-Preemptive");
			  printf("\n 2.] Priority Preemptive");
			  printf("\n Enter Option:");
			  scanf("%d",&op);
			  if(op==1)
			  {
				prinp(pr,p);
			  }
			  else if(op==2)
			  {
				prip(pr,p);
			  }
			  else
			  {
				printf("\n Not a Valid Option");
			  }
			   break;
			 }
		case 5:
			 {
			    exit(0);
			 }
		default:
			 printf("\n  Enter Valid Choice:");
	 }
     	 printf("\n Do you want to continue[Y|N]:");
     	 scanf("%s",&ch1);
   	}while(ch1=='y' || ch1=='Y');
	return 0;
}
---------------------------------------------------------------------------------------------------------------------------------------//
//FUNCTION DEFINITIONS

//PROCEDURE TO IMPLEMENT FCFS
void fcfs(int pr,process p[10])
{
    int i,j,burst;
    process sort[10],temp;

    for(i=1;i<=pr;i++)
	sort[i]=p[i];

    for(i=1;i<pr;i++)
    {
	for(j=i+1;j<=pr;j++)
	{
		if(sort[i].arr > sort[j].arr)
		{
		  temp=sort[i];
		  sort[i]=sort[j];
		  sort[j]=temp;
		}
	}
    }
    burst=sort[1].arr;
    printf("\n\n-----GANTT CHART-----\n\n");
    for(i=1;i<=pr;i++)
    {
	printf("P%d[%d--%d] | ",sort[i].pid,burst,burst+sort[i].bur);
	burst=burst+sort[i].bur;
	sort[i].tat=burst-sort[i].arr;
	sort[i].wt=(sort[i].tat-sort[i].bur);
    }
    display(pr,sort);
}

//---------------------------------------------------------------------------------------------------------------------------------------//				
//PROCEDURE TO IMPLEMENT SJF[NON-PREEMPTIVE]
void sjfnp(int pr,process p[10])
{
   process sort[10],temp;
   int i,j,burst,ind,cnt,b;
	    
   for(i=1;i<=pr;i++)
       sort[i]=p[i];

   sort1(pr,sort);

   ind=1;
   cnt=0;	
   burst=sort[ind].arr;

   printf("\n\n-----GANTT CHART-----\n\n");
   while(cnt!=pr)
   {    
    b=999;
    printf("P%d[%d--%d] | ",sort[ind].pid,burst,burst+sort[ind].bur);
    burst=burst+sort[ind].bur;
    sort[ind].tat=burst-sort[ind].arr;
    sort[ind].wt=(sort[ind].tat-sort[ind].bur);
    sort[ind].fg=1;
    cnt++;

    for(i=1;i<=pr;i++)
    {
      if(sort[i].fg!=1)
      {
	if(burst>sort[i].arr)
        {
	  if(b>sort[i].bur)
	   {
		ind=i;
	  	b=sort[i].bur;
           }   	
        }    	
      }
    }
  }
   display(pr,sort);	
 }
          
//---------------------------------------------------------------------------------------------------------------------------------------//
//PROCEDURE TO IMPLEMENT SJF[PREEMPTIVE]
void sjfp(int pr,process p[10])
{
   process sort[10],temp;
   int i,j,burst,ind=1,tot=0,flag=1,end=0,chk=0,prev=1,b;
	    
    for(i=1;i<=pr;i++)
    {
             sort[i]=p[i]; 
             tot+=p[i].bur;//CALCULATE TOTAL BURST TIME
    }	

    sort1(pr,sort);

    burst=end=sort[1].arr;
    prev=ind=1;
    printf("\n\n-----GANTT CHART-----\n\n");
    while(end!=tot)
    {
	b=999;
	for(i=1;i<=pr;i++)
	{
		if(sort[i].arr==end)
			sort[i].act=1;
	}
	for(i=1;i<=pr;i++)
    	{
		if(sort[i].act==1)
		{
			if(b>sort[i].rem)
			{
				b=sort[i].rem;
				ind=i;
			}		
		}	
	}
        if(prev!=ind)
        {
	    printf("P%d[%d--%d] | ",sort[prev].pid,burst,end);
	    burst=end;
        }
        end+=1;
        sort[ind].rem-=1;
        if(sort[ind].rem==0)
        {
  	 	sort[ind].act=0;
		sort[ind].tat=end-sort[ind].arr;
		sort[ind].wt=sort[ind].tat-sort[ind].bur;
        }	
        prev=ind;//MAINTAIN PREVIOUS INDEX 
        if(end==tot)
        {
	   printf("P%d[%d--%d] ",sort[prev].pid,burst,end);
	   burst=end;
        }
    }
    display(pr,sort);	
}

//---------------------------------------------------------------------------------------------------------------------------------------//
//PROCEDURE TO IMPLEMENT ROUND ROBIN
void rr(int pr,process p[10])
{ 
  process sort[10],temp;	
  queue *f,*r;
  int i,j,burst=0,end=0,ind=1,quantum=0,tot=0;
  f=r=NULL;
		
  for(i=1;i<=pr;i++)
	sort[i]=p[i];

  //SORT ACCORDING TO ARRIVAL TIME
  for(i=1;i<pr;i++)
  {
    for(j=i+1;j<=pr;j++)
    {
	if(sort[i].arr > sort[j].arr)
	{
	   temp=sort[i];
	   sort[i]=sort[j];
	   sort[j]=temp;
	}
    }
  }

   printf("\n Enter time-quantum:");
   scanf("%d",&quantum);

   printf("\n\n-----GANTT CHART-----\n\n");
   burst=end=sort[1].arr;
   sort[1].act=1;
   for(i=1;i<=pr;i++)
      tot=tot+sort[i].bur;//CALCULATE TOTAL BURST TIME

   while(end!=tot)
   {
     if(quantum < sort[ind].rem)
     {
	end+=quantum;
	sort[ind].rem-=quantum;
	printf("P%d[%d--%d] | ",sort[ind].pid,burst,end);
     }
     else
     {
	end+=sort[ind].rem;
	sort[ind].rem=0;
        sort[ind].tat=end-sort[ind].arr;
	sort[ind].wt=sort[ind].tat-sort[ind].bur;
	printf("P%d[%d--%d] | ",sort[ind].pid,burst,end);
     }
     burst=end;
     for(i=1;i<=pr;i++)
     {
	if(burst>=sort[i].arr && sort[i].act!=1)
	{
	  sort[i].act=1;
	  add(&f,&r,sort[i]);
	}
     }
     if (sort[ind].rem!=0)
	add(&f,&r,sort[ind]);
     //REMOVE NEXT PROCESS FROM READY QUEUE
     temp=del(&f,&r);
     for(i=1;i<=pr;i++)
     {
	if(temp.pid==sort[i].pid)
	{
	    ind=i;
	    break;
	}
    }
 }
  display(pr,sort);
}

//--------------------------------------------------------------------------------------------------------------------------------------//
//PROCEDURE TO IMPLEMENT PRIORITY NONPREEMPTIVE
void prinp(int pr,process p[10])
{
    int i,j,burst,pri,ind,p1,cnt;
    process sort[10],temp;

    for(i=1;i<=pr;i++)
    	sort[i]=p[i];

    sort2(pr,sort);	

    printf("\n\n-----GANTT CHART-----\n\n");
    burst=sort[1].arr;
    ind=1;
    cnt=0;
    while(cnt!=pr)
    {
	sort[ind].act=1;
	printf("P%d[%d--%d] | ",sort[ind].pid,burst,burst+sort[ind].bur);
	cnt+=1;
	burst+=sort[ind].bur;
	sort[ind].tat=burst-sort[ind].arr;
	sort[ind].wt=sort[ind].tat-sort[ind].bur;
        p1=999;
	for(i=1;i<=pr;i++)				  
	{
		if(p1 > sort[i].pri && sort[i].act!=1)
		{
			p1=pri;
			ind=i;
		}
	}
    }
   display(pr,sort);
}

//---------------------------------------------------------------------------------------------------------------------------------------//
//PROCEDURE TO IMPLEMENT PRIORITY(PREEMPTIVE)
void prip(int pr,process p[10])
{
    int i,j,burst,pri,ind,p1,cnt,tot=0,end,prev;
    process sort[10],temp;

    for(i=1;i<=pr;i++)
    {
    	sort[i]=p[i];
	tot+=p[i].bur;
    }
	
    sort2(pr,sort);

    printf("\n\n-----GANTT CHART-----\n\n");	

    burst=end=sort[1].arr;
    prev=ind=1;
    
    while(end!=tot)
    {
	p1=999;
	for(i=1;i<=pr;i++)
	{
		if(sort[i].arr==end)
			sort[i].act=1;
	}
	for(i=1;i<=pr;i++)
    	{
		if(sort[i].act==1)
		{
			if(p1 > sort[i].pri)
			{
				p1=sort[i].pri;
				ind=i;
			}		
		}	
	}
        if(prev!=ind)
        {
	    printf("P%d[%d--%d] | ",sort[prev].pid,burst,end);
	    burst=end;
        }
        end+=1;
        sort[ind].rem-=1;
        if(sort[ind].rem==0)
        {
  	 	sort[ind].act=0;
		sort[ind].tat=end-sort[ind].arr;
		sort[ind].wt=sort[ind].tat-sort[ind].bur;
        }	
        prev=ind;//MAINTAIN PREVIOUS INDEX 
        if(end==tot)
        {
	   printf("P%d[%d--%d] ",sort[prev].pid,burst,end);
	   burst=end;
        }
    }
    display(pr,sort);	
}
//---------------------------------------------------------------------------------------------------------------------------------------//
void sort2(int pr,process sort[10])
{
  process temp;	
  int i,j;  	
  for(i=1;i<pr;i++)
    {
	for(j=i+1;j<=pr;j++)
	{
		if(sort[i].arr > sort[j].arr)
		{
		  	  temp=sort[i];
	  		  sort[i]=sort[j];
	  		  sort[j]=temp;
		}	
		else if(sort[i].arr == sort[j].arr)
		{
	  		if(sort[i].pri > sort[j].pri)
	  		{
	    			temp=sort[i];
	    			sort[i]=sort[j];
	    			sort[j]=temp;
	  		}
		}
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------//
//SORT ACCORDING TO ARRIVAL TIME FOLLOWED BY BURST TIME
void sort1(int pr,process sort[10])
{
  int i,j;
   process temp;	 
  for(i=1;i<pr;i++)
   {
    for(j=i+1;j<=pr;j++)
    {
	if(sort[i].arr > sort[j].arr)
	{
	  temp=sort[i];
	  sort[i]=sort[j];
	  sort[j]=temp;
	}
	else if(sort[i].arr == sort[j].arr)
	{
	  if(sort[i].bur > sort[j].bur)
	  {
	    temp=sort[i];
	    sort[i]=sort[j];
	    sort[j]=temp;
	  }
	}
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------------------------//
//TO DISPLAY TOTAL TABLE ALONG WITH TURNAROUND TIME AND WAITING TIME
void display(int pr,process sort[10])
{
  int i,j;
  float ttat=0,twt=0;
  process temp;	
  for(i=1;i<pr;i++)
  {
    for(j=i+1;j<=pr;j++)
    {
     if(sort[i].pid > sort[j].pid)
     {
      temp=sort[i];
      sort[i]=sort[j];
      sort[j]=temp;
     }
    } 
  }
  printf("\n\n-----TABULAR DATA-----\n\n");
  printf("\nProcess\t    Arr.Time\t   Burst Time\t   Turnaround\t    Waiting");
  for(i=1;i<=pr;i++)
  {
      ttat+=sort[i].tat;
      twt+=sort[i].wt;
      printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i,sort[i].arr,sort[i].bur,sort[i].tat,sort[i].wt);
   }
   ttat=ttat/pr;
   twt=twt/pr;
   printf("\nAverage Turnaround Time :%.2f",ttat);
   printf("\nAverage Waiting Time :%.2f\n",twt);
}
