// Implement Memory allocation strategies - First Fit,Best Fit,Next Fit,Worst Fit


#include<stdio.h>
#include<stdlib.h>

//function to create dummy array
int* create(int *holes,int hno)
{
	int i,*h;
	h=(int *)malloc(hno * sizeof(int));
	for(i=0;i<hno;i++)
		h[i]=holes[i];
	return h;
}

//function for first fit
int firstfit(int *holes,int *process,int pno,int hno)
{
	int i,j,flag;
	for(i=0;i<pno;i++)
	{
		flag=0;
		printf("\nIncoming process p%d of size %dk",i+1,process[i]);
		for(j=0;j<hno;j++)
		{
			if(holes[j]>=process[i] && holes[j])
			{
				printf("\nProcess alloted a hole of size:%dk",holes[j]);
				holes[j]-=process[i];
				printf("\nNew list of holes is : ");
				for(j=0;j<hno;j++)
					if(holes[j])
						printf("%dk, ",holes[j]);
				flag=1;
				break;
			}
		}
		if(!flag)
			printf("\nEnough space not available for process p%d(%dk)",i+1,process[i]);
	}
}


//function for best fit
int bestfit(int *holes,int *process,int pno,int hno)
{
	int i,j,flag,min=9999,minj;
	for(i=0;i<pno;i++)
	{
		flag=0;
		min=9999;
		printf("\nIncoming process p%d of size %dk",i+1,process[i]);
		for(j=0;j<hno;j++)
		{
			if(holes[j]==process[i])
			{
				printf("\nProcess alloted a hole of size:%dk",holes[j]);
				flag=1;
				minj=j;
				break;				
			}
			else if(holes[j]>process[i])
			{
				if(holes[j]<min)
				{
					min=holes[j];
					minj=j;
					flag=1;
				}
			}
		}
		if(flag)
		{
			printf("\nProcess alloted a hole of size:%dk",holes[minj]);
			holes[minj]-=process[i];
			printf("\nNew list of holes is : ");
			for(j=0;j<hno;j++)
				if(holes[j])
					printf("%dk, ",holes[j]);
		}
		else
			printf("\nEnough space not available for process p%d(%dk)",i+1,process[i]);
	}
}  


//function for next fit
int nextfit(int *holes,int *process,int pno,int hno)
{
	int i,j,flag,prev=0,k;
	for(i=0;i<pno;i++)
	{
		flag=0;
		printf("\nIncoming process p%d of size %dk",i+1,process[i]);
		for(j=prev,k=0;k<hno;k++,j=(j+1)%hno)
		{
			if(holes[j]>=process[i] && holes[j])
			{
				printf("\nProcess alloted a hole of size:%dk",holes[j]);
				holes[j]-=process[i];
				prev=j;
				printf("\nNew list of holes is : ");
				for(j=0;j<hno;j++)
					if(holes[j])
						printf("%dk, ",holes[j]);
				flag=1;
				break;
			}
		}
		if(!flag)
			printf("\nEnough space not available for process p%d(%dk)",i+1,process[i]);
	}
}

//func to find hole with max capacity
int find_max(int *holes,int hno)
{
	int i,max=holes[0],maxi=0;
	for(i=1;i<hno;i++)
	{
		if(holes[i]>max)
		{
			max=holes[i];
			maxi=i;
		}
	}
	return maxi;
}
//func for worst fit algo
int worstfit(int *holes,int *process,int pno,int hno)
{
	int i,j,flag;
	for(i=0;i<pno;i++)
	{
		printf("\nIncoming process p%d of size %dk",i+1,process[i]);
		if(!(j=find_max(holes,hno)))
		{
			printf("\nAvailable mem is over rest processes cannot be allocated mem.........");
			return 0;
		}	
		if(holes[j]<process[i])
			printf("\nEnough space not available for process p%d(%dk)",i+1,process[i]);
		else
		{
			printf("\nProcess alloted a hole of size:%dk",holes[j]);
			holes[j]-=process[i];
			printf("\nNew list of holes is : ");
			for(j=0;j<hno;j++)
				if(holes[j])
					printf("%dk, ",holes[j]);
		}		
	}
}
int main()
{
	int *holes,*process,pno,hno,i,ch;
	printf("\nEnter no of holes:");
	scanf("%d",&hno);
	holes=(int *)malloc(hno * sizeof(int));
	printf("\nEnter size of holes:");
	for(i=0;i<hno;i++)
	{
		printf("\n[%d]:",i+1);
		scanf("%d",(holes+i));
	}
	printf("\nEnter no of processes:");
	scanf("%d",&pno);
	process=(int *)malloc(pno * sizeof(int));
	printf("\nEnter size of processes:");
	for(i=0;i<pno;i++)
	{
		printf("\n[%d]:",i+1);
		scanf("%d",(process+i));
	}	
	while(1)
	{
		printf("\n>>>>>>>>>>>>>>>>>>>>>>MENU<<<<<<<<<<<<<<<<<<<<<<<<<<<\
		\n1.First Fit\
		\n2.Best Fit\
		\n3.Next Fit\
		\n4.Worst Fit\
		\n5.Exit\
		\nEnter choice(1-4):");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:
				firstfit(create(holes,hno),process,pno,hno);
				break;
			case 2:	
				bestfit(create(holes,hno),process,pno,hno);
				break;
			case 3:
				nextfit(create(holes,hno),process,pno,hno);
				break;
			case 4:
				worstfit(create(holes,hno),process,pno,hno);
				break;
			case 5:
				exit(0);
			
		}//switch ends
	}//while ends
}
