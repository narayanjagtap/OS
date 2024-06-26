#include<stdio.h>
#include<stdlib.h>

typedef struct fr
{
	int pgn;
	int pos;
}fr;
fr fr1[10];
int st1,st[25],fs;
int q[25],r,f;

void input();
void output();
void fifo();
void optimal();
void lru();

void main()
{
	int i,ch;

	printf("\n Enter the total no. of pages of reference string:");
	scanf("%d", &st1);

	printf("\nEnter the page no.s:\n");
	for(i=0;i<st1;i++)
	{
		scanf("%d",&st[i]);
		
		
	}
	

	printf("\n Enter the no of frames:");
	scanf("%d",&fs);
	
	do
	{
		printf("\n\n------------MENU---------------");
		printf("\n 1.FIFO");
		printf("\n 2.OPTIMAL");
		printf("\n 3.LRU");
		printf("\n 4.EXIT");
		printf("\n---------------------------------");
		printf("\n\t Enter your choice:\t");
		scanf("%d",&ch);
		switch(ch)
		{	
			case 1:fifo();break;
			case 2:optimal();break;
			case 3:lru();break;
			case 4:exit(0);
			default:printf("\n Wrong choice Entered...");break;
		}
	}while(ch=4);
	
}



void output(int a)
{
	int i;
	printf("\n->%d|Page frame-:|",st[a]);
	for(i=0;i<fs;i++)
	{
		if(fr1[i].pgn!=999)
		printf("%d|",fr1[i].pgn);
		else
		printf(" |",fr1[i].pgn);
	}
	printf("\t Page Fault");
}

void fifo()
{
	int i,j,pgf=0,fp,flg=0;
	
	for(i=0;i<fs;i++)
	fr1[i].pgn=999,fr1[i].pos=0;
	r=f=0;
	for(j=0;j<fs;j++)
	{
		fr1[j].pgn=st[j];
		fr1[j].pos=j;
		q[r++]=st[j];
		pgf++;
		output(j);
	}
	for(i=fs;i<st1;i++)
	{
		flg=0;
		for(j=0;j<fs;j++)
		if(fr1[j].pgn==st[i])
		{
			printf("\n->%d|Page frame-:| | | |",st[i]);
			flg=1;
		}
		if(flg==0)
		{
			q[r++]=st[i];
			fp=q[f++];
			pgf++;
			for(j=0;j<fs;j++)
			if(fr1[j].pgn==fp)
			fr1[j].pgn=st[i];
			output(i);
		}
	}
	printf("\n Total no. of page faults-:%d",pgf);
	printf("\n-----------------------------------");
	
}

void optimal()
{
	int i,j,pgf=0,k,cnt,fp,flg=0;
	
	for(i=0;i<fs;i++)
	fr1[i].pgn=999,fr1[i].pos=0;
	for(j=0;j<fs;j++)
	{
		fr1[j].pgn=st[j];
		pgf++;
		output(j);
	}
	for(i=fs;i<st1;i++)
	{
		flg=0;
		for(j=0;j<fs;j++)
		if(fr1[j].pgn==st[i])
		{
			printf("\n->%d|page frame-:| | | |",st[i]);
			flg=1;
			break;
		}
		if(flg==0)
		{
			for(j=0;j<fs;j++)
			fr1[j].pos=0;
			k=i+1;
			cnt=0;
			while(cnt<fs-1&&k<st1)
			{
				cnt=0;
				for(j=0;j<fs;j++)
				if(fr1[j].pgn==st[k])
				fr1[j].pos=1;
				for(j=0;j<fs;j++)
				if(fr1[j].pos==1)
				cnt++;
				k++;
			}
			pgf++;
			for(j=0;j<fs;j++)
			if(fr1[j].pos==0)
			fr1[j].pgn=st[i];
			output(i);
		}
	}
	printf("\n Total no. of page faults:%d",pgf);
	printf("\n------------------------------------");
	
}

void lru()
{
	int i,j,pgf=0,k,cnt,fp,flg=0;
	
	for(i=0;i<fs;i++)
	fr1[i].pgn=999,fr1[i].pos=0;
	for(j=0;j<fs;j++)
	{
		fr1[j].pgn=st[j];
		pgf++;
		output(j);
	}
	for(i=fs;i<st1;i++)
	{
		flg=0;
		for(j=0;j<fs;j++)
		if(fr1[j].pgn==st[i])
		{
			printf("\n->%d|Page frame-:| | | |",st[i]);
			flg=1;
			break;
		}
		if(flg==0)
		{
			for(j=0;j<fs;j++)
			fr1[j].pos=0;
			k=i-1;
			cnt=0;
			while(cnt<fs-1)
			{
				cnt=0;
				for(j=0;j<fs;j++)
				if(fr1[j].pgn==st[k])
				fr1[j].pos=1;
				for(j=0;j<fs;j++)
				if(fr1[j].pos==1)
				cnt++;
				k--;
			}
			pgf++;
			for(j=0;j<fs;j++)
			if(fr1[j].pos==0)
			fr1[j].pgn=st[i];
			output(i);
		}
	}
	printf("\n Total no. os page faults:%d",pgf);
	printf("\n------------------------------------");
	
}



