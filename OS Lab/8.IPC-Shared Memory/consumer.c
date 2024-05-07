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
key_t getkey();
void consume_items(int running, ITEM_SHARED*);


int main()
{
	int running = 1;
	ITEM_SHARED *shm_ptr;
	char buffer[SZ];
	
	int shm_id;

	shm_id = shared_init();
	printf("shm_id = %d\n",shm_id);
	if(shm_id < 0)
	{
		printf("consumer : shmget eror\n");
		exit(-1);
	}

	shm_ptr = attach_shm(shm_id);

	if((int)shm_ptr == -1)
	{
		printf("consumerr:shmat error\n");
		exit(-1);
	}
	printf("memory attached at %x address\n",(int)shm_ptr);
	consume_items(running , shm_ptr);
return 0;
}
key_t getkey()
{
    key_t mykey = ftok(",",'C');
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

void consume_items(int running , ITEM_SHARED *shm_ptr)
{
	shm_ptr -> status = 0;

	while(running)
		{
		if (shm_ptr -> status)
			{
				printf("consumed: %s\n" , shm_ptr -> msg);
				sleep(rand() % 4);
				shm_ptr -> status = 0;
				if(strncmp(shm_ptr ->msg, "exit", 3) == 0)
					running = 0;

			}
		}
}

