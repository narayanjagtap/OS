/*  Assignment No. 5: Thread synchronization and mutual exclusion using mutex. Application to demonstrate:
Reader-Writer problem with readers priority.*/


#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>

#define R 5
#define W 5

pthread_mutex_t lock,rlock;
int key=0,rc=0;

void readerfunc(void *ptr)
{
	int k;
	k=(int *)ptr;
	while(1)
	{
	sleep(rand()%8);
	pthread_mutex_lock(&rlock);
	rc++;
		if(rc==1)
		{
		pthread_mutex_lock(&lock);
		}
	pthread_mutex_unlock(&rlock);
	printf("\nReader %d is reading the value : %d",k,key);

	pthread_mutex_lock(&rlock);
	rc--;
		if(rc==0)
		{
		pthread_mutex_unlock(&lock);
		}
		pthread_mutex_unlock(&rlock);
	}

}

void writerfunc(void *ptr)
{
	int k=(int *)ptr;
	while(1)
	{
	sleep(rand()%8);
	pthread_mutex_lock(&lock);
	key++;
	printf("\nWriter %d is writing the value : %d",k,key);
	pthread_mutex_unlock(&lock);
	}

}

int main(int argc,char *argv)
{
pthread_t reader[R],writer[W];
int i;

pthread_mutex_init(&lock,NULL);
pthread_mutex_init(&rlock,NULL);

for(i=0;i<R;i++)
pthread_create(&reader[i],NULL,readerfunc,(void *)i);

for(i=0;i<W;i++)
pthread_create(&writer[i],NULL,writerfunc,(void *)i);

for(i=0;i<R;i++)
pthread_join(reader[i],NULL);

for(i=0;i<W;i++)
pthread_join(writer[i],NULL);

return(0);
}

