#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
void binarysearch(long int a[],int n);
void main(int argc, char *argv[],char *envp[])
{
	int i, n=0;
	long a[10];
	for(i=1; argv[i]!=NULL; i++)	
	{
		a[i] = strtol(argv[i], NULL, 10);  //strtol: string to long integer
		n++;
	}
	printf("\n");
	printf("\nIn second child process. Process id is :  %d", getpid());
	printf("\nMy parent's process id is : %d", getppid());
	binarysearch(a,n);
}
void binarysearch(long int a[],int n)
{
	int i=1,j=n,mid,c=0,temp;
	printf("\nEnter the number you want to search:");
	scanf("%d",&temp);
	printf("\nIn binary search program");
	while(i<=j)
	{
		mid=(i+j)/2;
		if(temp==a[mid])
		{
			c=1;
			break;
		}
		else if(temp>a[mid])
		{
			i=mid+1;
		}
		else
		{
			j=mid-1;
		}
	}
	if(c==0)
		printf("\n%d is not found.",temp);
	else
		printf("\n%d is found at location %d.",temp,mid);
}

