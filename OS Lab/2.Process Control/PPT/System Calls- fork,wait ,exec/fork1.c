#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

//#include <unistd.h>

int main(void)
{
pid_t pid;   
printf("Hello \n");
printf("pid of parent process is:%d ",getpid()); 
   pid=fork();
printf("pid of child process is:%d ",getpid()); 
   printf("bye\n");
   return 0;
}
