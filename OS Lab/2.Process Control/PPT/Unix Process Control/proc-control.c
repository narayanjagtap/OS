/*
Title :- Process Control in UNIX
***************************************************************************** 
*/

#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#define MAX 20

int n;

void accept_nos(int arr[MAX])
{
	int i;
	printf("\n\tEnter the number of elements:");
	scanf("%d",&n);
	
	printf("\n\t Enter the elements:\n");
	for(i = 0 ; i < n ; i++ )
	{
	printf("\n\t Element %d :", i+1);
	scanf("%d", &arr[i]);
	}
}

void accept_str(char str[])
{
	printf("\n Enter the sentence for calculating number of vowels and words :");
	fgets(str,256,stdin);	
}

void display(int arr[MAX], char str[])
{
	int i;
	printf("\n\t Array elements :\n");
	for( i = 0 ; i < n ; i++ )
	{
	printf("\t element [%d] : %d", i+1, arr[i]);
	printf("\n");
	}
	printf("\n");

	printf("\n\t Entered String is :\n");
	printf("\t%s\n", str);
}

void sort_asc(int arr[MAX])
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(arr[i]<arr[j])
			{
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
			}
		}
	}
	printf("\n\n\tThe Numbers In Ascending Order Are:\n\t ");
	for(i=0;i<n;i++)
	{
	printf("%d ",arr[i]);
	}	
}

void sort_desc(int arr[MAX])
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(arr[i]>arr[j])
			{
			temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
			}
		}
	}
	printf("\n\n\t The Numbers In Descending Order Are:\n\t ");
	for(i=0;i<n;i++)
	{
	printf("%d ",arr[i]);
	}	
}

void cnt_vowels(char str[])
{
	int j=0,cnt=0,a,e,i,o,u;
	    a=e=i=o=u=0;
	
	while(str[j]!='\0')
	{
			     if(str[j]=='a' || str[j]=='A')     a++;
            		else if(str[j]=='e' || str[j]=='E')	e++;
                        else if(str[j]=='i' || str[j]=='I')	i++;
                        else if(str[j]=='o' || str[j]=='O')	o++;
                        else if(str[j]=='u' || str[j]=='U')	u++;		
	      //if(str[i]=='a'||  str[i]=='e'|| str[i]=='i'|| str[i]=='o'|| str[i]=='u'||
		 //str[i]=='A'|| str[i] =='E'|| str[i]=='I'|| str[i]=='O'|| str[i]=='U')
	     // {
		//cnt++;
             // }
	      j++;
	}
	printf("\n Vowels Counting");

     		printf("\n Number of A  : %d",a);
                printf("\n Number of E  : %d",e);
                printf("\n Number of I  : %d",i);
                printf("\n Number of O  : %d",o);
                printf("\n Number of U  : %d",u);
                printf("\n Total vowels : %d",a+e+i+o+u);
	printf(" \n\t Total number of vowels in the given string is: %d\n",a+e+i+o+u);	
}

void cnt_words(char str[])
{
	int cnt=1,i=0;

	for(i=0;str[i]!='\0';i++)
        {
               if(str[i]==' ')
	       {
		cnt++;
	       }
	}
	printf(" \n\t Number of words in the given string is: %d",cnt);
}

int main()
{
	char str[50];
	int arr[MAX], *status=NULL;
	pid_t cpid;
	
	fflush(stdout);	

	accept_str(str);
	accept_nos(arr);

	printf("\n\t Original numbers are : \n");
	display(arr,str);	
	cpid = vfork();

	if( cpid == 0 )
	{
	printf("\n\t This is child process:");
	printf("\n\t My process id is : %d", getpid());
	printf("\n\t My Parent process id is : %d", getppid());
		
	sort_desc(arr);
	cnt_words(str);	
	exit(1);			
	}
	else
	{
	cpid = wait(status);
	printf("\n\n\t Parent process resumed after the execution of child process with PID %d", cpid);
	printf("\n\t My process id is : %d", getpid());
	printf("\n\t My Parent process id is : %d", getppid());
	sort_asc(arr);
	cnt_vowels(str);			
	}
return 0;	
}

