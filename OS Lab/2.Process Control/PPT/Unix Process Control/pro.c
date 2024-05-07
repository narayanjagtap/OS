/*

Title : Program where parent process sorts array elements in Descending order & Child 
        process sorts array elements in Ascending order 
Roll No :  
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

int n;
int asc (int no[20]) ;
int dsc (int no[20]) ;

int main()
{
    int i,k;
    int no[20];
    int str[20];

	printf("\n Enter the numbers for sorting:");
	scanf("%d",&n);
   
	printf("\n Enter the data:");
	{
    	for(i=0;i<n;i++)
   	scanf("%d",&no[i]);
	}

	pid_t pid=fork();
	if(pid==0)
	{ 
	printf("\n Child process pid=%d",getpid());
   	asc(no);
	} 
		if(pid<0)
		{   
    		printf("\n Forking ERROR:") ;
		}
		else
			{
    			printf("\n Parent process pid=%d",getpid()) ;    
    			dsc(no) ;
			}
return(0) ;
}



int asc(int no[20])
{
    int i,j,temp;
    for(i=0;i<n;i++)
    { 
      for(j=0;j<n;j++)
      {
          if(no[i]<no[j])
          {
                temp=no[i];
                no[i]=no[j];
                no[j]=temp;
          }
      }
    }
printf("\n Ascending order:\n") ;
for(i=0;i<n;i++)
{  
    printf("%d",no[i]) ;
    printf("\n") ;
}

return(0) ;
}




int dsc(int no[20])
{
  int i,j,temp;
  for(i=0;i<n;i++)
  {
     for(j=0;j<n;j++)
     {
          if(no[i]>no[j])
          {
                temp=no[i];
                no[i]=no[j];
                no[j]=temp;
          }
     }
  }
printf("\n Descending order:\n") ;
for(i=0;i<n;i++)
{  
    printf("%d",no[i]) ;
    printf("\n") ;
}

return(0) ;
}



