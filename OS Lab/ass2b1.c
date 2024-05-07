
//Binary Search

#include<stdio.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<unistd.h>


int binary_search(int a[10],int n);
void main(int argc,char *argv[])
{
	int n=argc,i,j=0,k,nos,a[n];
	printf("This is 2nd program whose id is=%d\n",getpid());
	for(i=0;i<n;i++)
  	{
      		k=atoi(argv[i]);
      		a[j]=k;
      		j++;
	}   
 
 	nos=binary_search(a,n); 
	if(nos==0)
	{
		printf("Number not present\n");
		exit(0);
	}
	else  
	{
		printf("Number is present at location= %d\n",nos);
		exit(0);
	}
}


int binary_search(int a[10],int n)				
{
	int low=0,high=n-1,mid,k;
	printf("Enter the number to be searched:\n");
	scanf("%d",&k);
   	while(low<=high)
   	{
       		mid=(low+high)/2;
       		
       		if(a[mid]==k)
           		return mid;

                else if(k<a[mid])
           		high=mid-1;

     		else 
           		low=mid+1;
    	}

    return 0;

}

