#include<stdio.h> 
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>

main()
{
	int file1,file2;

	file1 = mkfifo("fifo_server",0666); 

	if(file1<0) 
 	{
 	printf("Unable to create a fifo_server. \n");
 	exit(-1);
 	}

	file2 = mkfifo("fifo_client",0666);

	if(file2<0)
 	{
 	printf("Unable to create a fifo_client. \n");
 	exit(-1);
 	}

	printf("fifos server and client created successfuly. \n");
}



/*
 In One Terminal:

amol@amol-Aspire-5742:~$ gcc create-fifo.c
amol@amol-Aspire-5742:~$ ./a.out
fifos server and client created successfuly. 
amol@amol-Aspire-5742:~$ gcc server.c -o server
amol@amol-Aspire-5742:~$ ./server

 Data sent to client 
amol@amol-Aspire-5742:~$ ./server

Data sent to client
amol@amol-Aspire-5742:~$ ./server

Data sent to client
amol@amol-Aspire-5742:~$ 


In second terminal:

amol@amol-Aspire-5742:~$ gcc client.c -o client
amol@amol-Aspire-5742:~$ ./client
Choose the request to be sent to server from options below:
.
		 Enter 1 for O.S.Name 
                 Enter 2 for Distribution 
                 Enter 3 for Kernel version 
1

 ***Reply from server is Linux***
amol@amol-Aspire-5742:~$ ./client
Choose the request to be sent to server from options below:
.
		 Enter 1 for O.S.Name 
                 Enter 2 for Distribution 
                 Enter 3 for Kernel version 
2

 ***Reply from server is debian***
amol@amol-Aspire-5742:~$ ./client
Choose the request to be sent to server from options below:
.
		 Enter 1 for O.S.Name 
                 Enter 2 for Distribution 
                 Enter 3 for Kernel version 
3

 ***Reply from server is 2.6.32***
amol@amol-Aspire-5742:~$ 

*/
