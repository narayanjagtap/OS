#include<stdio.h> 
#include<fcntl.h>
#include<stdlib.h>

main()
{
 	FILE *file2;
 	int fifo_server,fifo_client;
 	char *buffer;
 	int choice;

 	printf("Choose the request to be sent to server from options below:\n.");
 	printf("\n\t\t Enter 1 for O.S.Name \n \
                       Enter 2 for Distribution \n \
                       Enter 3 for Kernel version \n");
 	scanf("%d",&choice);

 	fifo_server=open("fifo_server",O_RDWR);

 	if(fifo_server < 0)
  	{
  	printf("Error in opening file:\n.");
  	exit(-1);
  	}

 	write(fifo_server,&choice,sizeof(int));

 	fifo_client=open("fifo_client",O_RDWR);
 
 	if(fifo_client < 0) 
  	{
  	printf("Error in opening file:\n.");
  	exit(-1);
  	}

 	buffer=malloc(10*sizeof(char));

 	read(fifo_client,buffer,10*sizeof(char));
 	printf("\n ***Reply from server is %s***\n",buffer);

 	close(fifo_server);
 	close(fifo_client);
}


/*

Now to use these pipes, we will write two program's one to represent the server and other to represent the client. The server will read from the pipe fifo_server to which the client will send a request. On reciveing the request, the server will send the information to the client on fifo_client. 

The above code,server.c, reads the choice from fifo_server to which the client writes and depending on the request,the server responds with the relevant data by writing to fifo_client. 

The above code,client.c, sends a request to the server by writing to the pipe fifo_server, and recieves the reply from the server by reading the pipe fifo_client. 

To see the pipe in operation, open two terminals and go the folder where the pipes have been created. 

Terminal 1: 


./server

 

The terminal will go into a wait state with the cursor blinking, waiting for request from client. 

Terminal 2: 


./client 

 

The client will prompt to make a choice of request to be sent to the server, enter number 1,2 or 3 


Choose the request to be sent to server from options below
  Enter 1 for O.S.Name 
                 Enter 2.Distribution 
                 Enter 3.Kernel version

 

This number will be sent to the server and the client will go into a wait state, waiting for the server to respond. 

After a few seconds you should see the reponse from the server being printed on the client terminal. 

Note: wait for 10 seconds for the output to appear as the server has a sleep for 10 seconds, this is required to allow some time for the client to start its read operation on the fifo_client pipe. 

for eg if we entered option 2, the response would be 

output on client terminal: 


 ***Reply from server is debian***

 
Ouput on server terminal : 


Data sent to client

 

Thus we were able to communicate between the two processes using the fifos, even though the pipes were not created by them. 

To use the pipes with out writing the server and client code we can use "cat" and "echo" commands. 

Terminal 1: 


cat fifo_server 

 

Terminal 2: 
echo "hello world" > fifo_server 

We should be able to see the "hello world" being printed on the Terminal 1. 

*/
