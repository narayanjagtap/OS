#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define MAXLINE 100

int main(void)
{
  int n, fd[2];
  pid_t pid;
  char line[MAXLINE];

  int i;char c;

  if (pipe(fd) < 0)
    
    fprintf(stderr, "pipe error \n");

  if ((pid = fork()) < 0)
    fprintf(stderr, "fork error \n");
    
  else if (pid > 0) {   /* parent */
    close(fd[0]);
    write(fd[1], "\nhello world\n", 12);
    printf("\n Parent Process:pid=%d",getpid());
  } else {              /* child */
    	  close(fd[1]);
          n=read(fd[0],line,MAXLINE);
          for(i = 0; i < n; i++) {
          c=toupper(line[i]);
          write(STDOUT_FILENO, &c, 1);
    printf("\n Child Process:pid=%d",getpid());
    }
  }
  return 0;
}



/*
amol@amol-Aspire-5742:~$ gcc pipe2.c
amol@amol-Aspire-5742:~$ ./a.out

 Parent Process:pid=2998

H Child Process:pid=2999
E Child Process:pid=2999
L Child Process:pid=2999
L Child Process:pid=2999
O Child Process:pid=2999
  Child Process:pid=2999
W Child Process:pid=2999
O Child Process:pid=2999
R Child Process:pid=2999
L Child Process:pid=2999
D Child Process:pid=2999

 Child Process:pid=2999
 Child Process:pid=2999amol@amol-Aspire-5742:~$ 
*/
