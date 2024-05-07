# include<stdio.h>
# include<unistd.h>
//# include<sys/types.h>
# include<stdlib.h>
int main()
{
pid_t pid;
pid=fork();
if (pid<0)
{ fprintf(stderr,"Fork failed");
exit(-1);}
else if (pid==0){
execlp("/bin/ls","ls",NULL);
}
else {
wait(NULL);
printf("Child Complete");
exit(0);
}}

