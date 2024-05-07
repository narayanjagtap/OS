#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/stat.h>

#define SZ 4096

typedef struct item_struct
{
	int status;   // status 1 if produced an item 0 otherwise
	char msg[SZ];
}ITEM_SHARED;

ITEM_SHARED *attach_shm(int);
int shared_init();
int remove_shared_memory(int shmid, ITEM_SHARED*);
key_t getkey();
void produce_items(int running, ITEM_SHARED*);
key_t getkey();
void produce_items(int running, ITEM_SHARED*);

int main()
{
	int running = 1;
	ITEM_SHARED *shm_ptr;
	char buffer[SZ];
	int ret_remove;
	int shm_id;
	shm_id = shared_init();
	printf("shm_id = %d\n",shm_id);
	if(shm_id < 0)
	{
		printf("producer : shmget eror\n");
		exit(-1);
	}

	shm_ptr = attach_shm(shm_id);

	if((int)shm_ptr == -1)
	{
		 printf("producer:shmat error\n");
		exit(-1);
	}
	printf("memory attached at %x address\n",(int)shm_ptr);
	produce_items(running,shm_ptr);
	ret_remove=remove_shared_memory(shm_id,shm_ptr);
	if(ret_remove == 0)
		printf("shared memory removed\n");
return 0;
}

void produce_items(int running, ITEM_SHARED *shm_ptr)
{
 char buffer[SZ];
	while(running)
	{
		while(shm_ptr->status==1)
		{
			sleep(1);
			printf("waiting for consumer\n");
		}         //inner while
		printf("producer: Enter an item to be produced\n");
		gets(buffer);
		strcpy(shm_ptr ->msg, buffer);
		shm_ptr->status=1;

		if(strncmp(buffer , "exit" , 3 )==0)
			running=0;

	}
}

key_t getkey()
{
    key_t mykey=ftok(",", 'C');
return (mykey);
}

int shared_init()
{
	int shm_id;
		key_t mykey = getkey();
		shm_id = shmget(mykey , SZ , IPC_CREAT | 0666);
return(shm_id);
}

ITEM_SHARED *attach_shm(int shm_id)
{
	ITEM_SHARED *shm_ptr;
	shm_ptr = (ITEM_SHARED*)shmat(shm_id, NULL , 0);
return shm_ptr;
}

int remove_shared_memory(int shm_id , ITEM_SHARED *shm_ptr)
{
	int ret_val1 , ret_val2;
	
	shmdt((void*)shm_ptr);
	ret_val2 = shmctl(shm_id , IPC_RMID , NULL);
	if (ret_val2 == -1)
		return -1;
	else
		return 0;
}
