/****************************************************************************/

			   /* PROGRAM FOR PREEMPTIVE SJF */
				 
/****************************************************************************/


#include<stdio.h>
#include<conio.h>
#include<graphics.h>

typedef struct queue
{
	int a[100];
	int front, rear;

} SQ;

typedef struct node
{
	int no, time;

} SN;

void main()
{
	void sjf(int [], int [], int);

	int gd=DETECT, gm, flag;
	int i, n, bst[100], at[100];
	char ch;

	initgraph(&gd, &gm, "");

	do
	{
		printf("\n\nENTER NO. OF PROCESSES : ");
		scanf("%d", &n);

		do
		{
			flag = 0;

			printf("\n\nENTER BURST TIME FOR EACH PROCESSES : \n\n");

			for(i=0; i<n; i++)
			{
				printf("\nFOR %d PROCESS : ", i+1);
				scanf("%d", &bst[i]);
			}

			for(i=0; i<n; i++)
			{
				if(bst[i] != 0)
					break;
			}

			if(i == n)
			{
				flag = 1;

				printf("\n\nENTER BURST TIME OF ANY OF THE PROCESS AS NON-ZERO");
			}

		} while(flag == 1);

		printf("\n\nENTER ARRIVAL TIME FOR EACH PROCESS : \n\n");

		for(i=0; i<n; i++)
		{
			printf("\nFOR %d PROCESS : ", i+1);
			scanf("%d", &at[i]);
		}

		cleardevice();

		sjf(bst, at, n);

		getch();

		cleardevice();

		printf("\n\nDO YOU WANT TO CONTINUE? (Y/N) : ");
		flushall();
		scanf("%c", &ch);

	} while(ch == 'y' || ch == 'Y');

	getch();
}

void sjf(int bst[], int at[], int n)
{
	void display(SN [], int);
	void draw(int [], int [], int [], int);

	SN s[100];
	SQ q;
	int i, j, k, p, cnt1, cnt2, prev, temp;
	int bt[100], toc[100], tac[100], wt[100], finish[100];

	for(i=0; i<100; i++)
	{
		finish[i] = 0;

		bt[i] = bst[i];
	}

	j = 0;

	for(i=1; i<n; i++)
	{
		if(at[j] > at[i])
			j = i;
	}

	q.front = 0;

	q.rear = 0;

	q.a[q.rear++] = j;

	cnt1 = 0;

	cnt2 = 0;

	p = 0;

	i = q.a[q.front];

	while(1)
	{
		cnt2++;

		if(bst[i] != 0)
			bst[i] = bst[i] - 1;

		if(bst[i] == 0)
		{
			toc[i] = cnt2;

			finish[i] = 1;
		}

		for(j=0; j<n; j++)
		{
			for(k=q.front; k<q.rear; k++)
			{
				if(j == q.a[k])
					break;
			}

			if(k != q.rear || finish[j] == 1)
				continue;

			else if(cnt2 == at[j])
				break;
		}

		if(j != n || finish[i] == 1)
		{
			prev = i;

			if(j != n)
				q.a[q.rear++] = j;

			if(finish[i] == 1)
				q.front++;

			for(j=q.front; j<q.rear-1; j++)
			{
				for(k=q.front; k<q.rear-1; k++)
				{
					if(bst[ q.a[k] ] > bst[ q.a[k+1] ])
					{
						temp = q.a[k];

						q.a[k] = q.a[k+1];

						q.a[k+1] = temp;
					}
				}
			}

			i = q.a[q.front];

			if(prev != i || q.front == q.rear)
			{
				k = cnt2 - cnt1;

				cnt1 = cnt2;

				s[p].no = prev + 1;

				s[p].time = k;

				p++;
			}
		}

		for(j=0; j<n; j++)
		{
			if(finish[j] == 0)
				break;
		}

		if(j == n)
			break;
	}

	display(s, p);

	getch();

	cleardevice();

	for(i=0; i<n; i++)
		tac[i] = toc[i] - at[i];

	for(i=0; i<n; i++)
		wt[i] = tac[i] - bt[i];

	draw(bt, tac, wt, n);
}

void display(SN s[], int n)
{
	int i, j, k, res, cnt1, cnt2;
	float p, q, m, x, y;
	char c[100];

	setcolor(LIGHTMAGENTA);

	sprintf(c, "GANTT CHART IS GIVEN BELOW : ");

	outtextxy(5, 20, c);

	res = 0;

	for(i=0; i<n; i++)
		res = res + s[i].time;

	m = (float) (620 / res);

	x = 5;

	y = 50;

	cnt2 = 0;

	for(i=0;i<n; i++)
	{
		j = s[i].no;

		k = s[i].time;

		cnt1 = cnt2;

		cnt2 = cnt2 + k;

		setcolor(LIGHTGREEN);

		p = x + (k * m);

		rectangle(x, y, p, y+20);

		setcolor(YELLOW);

		settextstyle(2, 0, 0);

		p = x + (k * m / 2) - 2;

		q = y + 5;

		sprintf(c, "P%d", j);

		outtextxy(p, q, c);

		setcolor(LIGHTCYAN);

		q = y + 25;

		p = x - 4;

		sprintf(c, "%d", cnt1);

		outtextxy(p, q, c);

		p = x + (k * m) - 4;

		sprintf(c, "%d", cnt2);

		outtextxy(p, q, c);

		x = x + (k * m);

		delay(200);
	}
}

void draw(int bst[], int tac[], int wt[], int n)
{
	int i, j, k, l,m, p, q, x, y, sum;
	float avg;
	char c[100];

	x = 5;

	y = 50;

	settextstyle(0, 0, 1);

	sprintf(c, "  PROCESS NO. ");

	i = textwidth(c);

	setcolor(YELLOW);

	rectangle(x, y, x+i, y+24);

	setcolor(LIGHTMAGENTA);

	outtextxy(x, y+8, c);

	j = x + i;


	sprintf(c, "  BURST TIME  ");

	i = textwidth(c);

	setcolor(YELLOW);

	rectangle(j, y, j+i, y+24);

	setcolor(LIGHTMAGENTA);

	outtextxy(j, y+8, c);

	k = j + i;


	sprintf(c, "  TURN AROUND TIME  ");

	i = textwidth(c);

	setcolor(YELLOW);

	rectangle(k, y, k+i, y+24);

	setcolor(LIGHTMAGENTA);

	outtextxy(k, y+8, c);

	m = k + i;


	sprintf(c, "  WAITING TIME  ");

	i = textwidth(c);

	setcolor(YELLOW);

	rectangle(m, y, m+i, y+24);

	setcolor(LIGHTMAGENTA);

	outtextxy(m, y+8, c);

	l = m + i;


	p = y + 24;

	for(i=0; i<n; i++)
	{
		q = p + 16;

		setcolor(YELLOW);

		rectangle(x, p, j, q);

		setcolor(LIGHTCYAN);

		sprintf(c, "      %2d", i+1);

		outtextxy(x, p+4, c);


		setcolor(YELLOW);

		rectangle(j, p, k, q);

		setcolor(LIGHTCYAN);

		sprintf(c, "      %2d", bst[i]);

		outtextxy(j, p+4, c);


		setcolor(YELLOW);

		rectangle(k, p, m, q);

		setcolor(LIGHTCYAN);

		sprintf(c, "      %2d", tac[i]);

		outtextxy(k, p+4, c);


		setcolor(YELLOW);

		rectangle(m, p, l, q);

		setcolor(LIGHTCYAN);

		sprintf(c, "      %2d", wt[i]);

		outtextxy(m, p+4, c);


		p = q;
	}

	y = p + 50;

	setcolor(LIGHTRED);

	sprintf(c, "AVERAGE TURN AROUND TIME : ");

	outtextxy(5, y, c);

	for(i=0; i<n; i++)
		sum = sum + tac[i];

	avg = (float) (sum / n);

	i = textwidth(c);

	x = 5 + i + 20;

	setcolor(LIGHTGREEN);

	sprintf(c, "%f", avg);

	outtextxy(x, y, c);


	y = y + 30;


	setcolor(LIGHTRED);

	sprintf(c, "AVERAGE WAITING TIME : ");

	outtextxy(5, y, c);

	for(i=0; i<n; i++)
		sum = sum + wt[i];

	avg = (float) (sum / n);

	i = textwidth(c);

	x = 5 + i + 20;

	setcolor(LIGHTGREEN);

	sprintf(c, "%f", avg);

	outtextxy(x, y, c);
}
