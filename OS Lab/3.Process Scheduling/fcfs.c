
#include<stdio.h>
main()


    {
    float avgwt,avgtt;
    char pname[10][10],c[10][10];
    int wt[10],tt[10],bt[10],at[10],t,q,i,n,sum=0,sbt=0,ttime,j,ss=0;
    printf("\n\nEnter the number of processes:");
    scanf("%d",&n);
    printf("\n\n Enter the NAME, BURST TIME and ARRIVAL TIME of thr process");
    for(i=0;i<n;i++)


        {
        printf("\n\nNAME : ");
        scanf("%s",&pname[i]);
        printf("\n\nBURST TIME : ");
        scanf("%d",&bt[i]);
        printf("\n\n ARRIVAL TIME :");
        scanf("%d",&at[i]);
    }
    for(i=0;i<n;i++)
    for(j=i+1;j<n;j++)


        {
        if(at[i]>at[j])


            {
            t=at[i];
            at[i]=at[j];
            at[j]=t;
            q=bt[i];
            bt[i]=bt[j];
            bt[j]=q;
            strcpy(c[i],pname[i]);
            strcpy(pname[i],pname[j]);
            strcpy(pname[j],c[i]);
        }
    }
    wt[0]=0;
    for(i=0;i<n;i++)


        {
        wt[i+1]=wt[i]+bt[i];
        sum=sum+(wt[i+1]-at[i]);
        tt[i]=wt[i]+bt[i];
        ss=ss+bt[i];
    }
    avgwt=(float) sum/n;
    avgtt=(float) sbt/n;
    printf("\n\nAverage waiting time=%f",avgwt);
    printf("\n\nAverage turn-around time=%f",avgtt);
    printf("\n\n GANTT CHART\n");
    for(i=0;i<n;i++)


        {printf("|\t%s\t",pname[i]);
    }
    printf("\n");
    for(i=0;i<n;i++)


        {
        printf("%d\t\t",wt[i]);
    }
    printf("%d\n",ss);
    printf("\n");
}

		
