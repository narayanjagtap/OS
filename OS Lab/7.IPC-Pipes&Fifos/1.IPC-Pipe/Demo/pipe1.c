/*pipe*/

#include<stdio.h> 
#include<unistd.h>
#include<sys/types.h>

char string1[] = "\n Hello, this is the message from parent to child";
char string2[] = "\n Hello, this is the message from child to parent";

int main ()
{
  char buf[1024];
  int fds1[2], fds2[2];
  int childr, childw, parentr, parentw;
  pid_t pid;
  
  pipe (fds1);
  pipe (fds2);
  childr  = fds1[0];
  childw  = fds1[1];
  parentr = fds2[0];
  parentw = fds2[1];

  if(pid=fork()>0)
  {
   /* the parent process */
    printf("\n Parent Process:pid=%d",getpid());
    close (childr); close (childw);

    write(parentw,string1,sizeof(string1));

    read(parentr,buf,sizeof(string2));
    printf ("\n Parent: %s\n", buf);
    
  }
  else

  { /* the child process */

    printf("\n Child Process:pid=%d",getpid());
    close(parentr); close(parentw);

    write(childw,string2,sizeof(string2));

    read(childr,buf,sizeof(string1));

    printf ("\n Child: %s\n", buf);
    
  }
}



/*
amol@amol-Aspire-5742:~$ gcc pipe1.c
amol@amol-Aspire-5742:~$ ./a.out

 Parent Process:pid=2948
 Parent: 
 Hello, this is the message from parent to child

 Child Process:pid=2949
 Child: 
 Hello, this is the message from child to parent
amol@amol-Aspire-5742:~$ 
*/



