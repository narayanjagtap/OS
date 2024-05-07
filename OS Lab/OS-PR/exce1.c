#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
void bubblesort(int a[],int n);
pid_t id;
void main()
{
	int a[10],n,i;
	char *argv[12];
	for(i=0; i<12; i++)
	{
		argv[i] = (char *) malloc(20);          //memory allocation
	}
	printf("\n\nEnter the number of elements in the array: ");
	scanf("%d", &n);
	printf("Enter the elements: ");
    	for(i=0;i<n;i++)
	{
      		scanf("%d",&a[i]);
	}
	printf("\nIn Parent process.\nParent process id is : %d", getpid());
	bubblesort(a,n);
	switch(id = fork())               //process creation
	{
		case -1: printf("\nError in fork.");
		break;
		case 0: printf("\nIn child process.\nChild process id is : %d ", getpid());
		printf("\nParent process id of child process is : %d ", getppid());
		for(i=0; i<n; i++)
		{
			sprintf(argv[i+1], "%d", a[i]);
		}
		argv[0] = "binsearch";
	        argv[n+2] = NULL;
    
		execv("binsearch",argv);
		printf("Error");
                         
		break;
		default: printf("\nSorted elements: ");          //parent process
		for(i=0;i<n;i++)       
			printf(" %d",a[i]);
		printf("\n");
		wait(0);
		printf("\nEnd of parent process\n.");

	}
}
void bubblesort(int a[],int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(a[i]>a[j])
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
}

