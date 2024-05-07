#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
void bubble(int a[],int n);
void selection(int a[],int n);
void display(int a[],int n);
int main()
{
	int a[10],n,i;
        pid_t id;
        printf("Enter the number of elements : ");
        scanf("%d",&n);
        printf("\nEnter the elements : ");
        for(i=0;i<n;i++)
        {
        	scanf("%d",&a[i]);
        }
	id = fork();     //create process
        switch(id)
        {
                case -1 : printf("\nError in Fork");
                break; 
                case 0 : printf("\nChild process ID : %d",getpid());   // child process
                         printf("\nMy Parent Process ID : %d",getppid());
                         bubble(a,n);
			 display(a,n);                                                       
                         printf("\nI am Orphan...");
                break;
                default : printf("\nParent process ID : %d",getpid());  //parent process
                          selection(a,n);
			  display(a,n);                   
                          printf("\n");                                                                       
        }
}
void bubble(int a[],int n)
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
void display(int a[],int n)
{
	int i;
	printf("\n");
	printf("Sorted array: ");
	for(i=0;i<n;i++)
	{
		printf("%d ",a[i]);
	}
}
void selection(int a[],int n)
{
	int min,temp;
	for(int i=0;i<n;i++)
	{
		min = i;
		for(int j=i+1;j<n;j++)
		{
			if(a[j]>a[min])
			{
				min=j;
			}
		}
		temp=a[i];
		a[i]=a[min];
		a[min]=temp;
	}
}
/*-----------------------OUTPUT--------------------------

com03@com03-Veriton-M200-A58:~/shraddha$ gcc as2orphan.c 
com03@com03-Veriton-M200-A58:~/shraddha$ ./a.out	 
Enter the number of elements : 7

Enter the elements : 6 4 1 9 3 2 8

Parent process ID : 4738
Sorted array: 9 8 6 4 3 2 1 

Child process ID : 4740
My Parent Process ID : 4738
Sorted array: 1 2 3 4 6 8 9 
I am Orphan...com03@com03-Veriton-M200-A58:~/shraddha$ 
*/
