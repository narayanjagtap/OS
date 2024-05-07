  
/*
Implement the C program in which main program accepts an integer  array. Main program uses the FORK system call to create a new process called child process.Parent process sorts an interger array and passes the sorted array to child process through the command line arguments of EXECVE system call. the child process uses EXECVE system call to load,new program , that uses this sorted array for performing the binary search the particuler item in array.
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void ascending(int *a,int nElem);

int main(int argc,char *argv[])
{
	int pid,k;
	int nElem=argc - 2;
	char *args[nElem+1];
	int i,elem;
	int j=2,l=0;
	int a[nElem];
	printf("nElem=%d\n",nElem);
	args[0]=argv[1];
	for(i=1;i<=nElem;i++)
	{
		args[i]=argv[j];
		j++;
	}
	args[i]=(char*)0;
	for(i=1;i<=nElem;i++)
	{
		elem=atoi(args[i]);
		a[l]=elem;
		l++;
	}
	ascending(a,nElem);
	for(i=0;i<nElem;i++)
	{
		sprintf(args[i+1],"%d",a[i]);
	}	
	pid=fork();
	if(pid==0)
	{
		printf("\nExecuted by child process\n");
		printf("The child  process ID is %d\n",(int)getpid());
		printf("The parent process ID is %d\n",(int)getppid());
		execve(argv[1],args,NULL);
	}
	else
	{
		k=wait(0);
		printf("\nExecuted by parents process\n ");
		printf("The parent process ID is %d\n",(int)getpid());
		printf("The shell  process ID is %d\n",(int)getppid());
	}
	return 0;
}

void ascending(int *a , int nElem)
{
	int i,j,temp;
	
	for(i=0;i<nElem;i++)
	{
		for(j=i+1;j<nElem;j++)
		{
			if(a[i]>a[j])
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	printf("sorted in ascending order\n");
	for(i=0;i<nElem;i++)
	{
		printf("%d\t",a[i]);
	}
	printf("\n");	
}

/*
student@student-OptiPlex-390:~/Desktop/OS$ gcc ass2b.c -o p.out
student@student-OptiPlex-390:~/Desktop/OS$ gcc ass2b1.c -o s
student@student-OptiPlex-390:~/Desktop/OS$ ./p.out s 5 8 1 3
nElem=4
sorted in ascending order
1	3	5	8	

Executed by child process
The child  process ID is 2811
The parent process ID is 2810
This is 2nd program whose id is=2811
Enter the number to be searched:
8
Number is present at location= 4

Executed by parents process
 The parent process ID is 2810
The shell  process ID is 2783
student@student-OptiPlex-390:~/Desktop/OS$ 

*/
