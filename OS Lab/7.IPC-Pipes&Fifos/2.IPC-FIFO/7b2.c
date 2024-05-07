#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
	int fd2,fd1,i,j,k,chars,words,s;
char buf[512],str[512];

fd1=open("myfifo1",O_RDONLY);
read(fd1,buf,sizeof(buf));
printf("\nDatareceived is:\n");
   for(i=0;i<strlen(buf);i++)
   {
   		printf("%c",buf[i]);
   }

//printf("%s",buf);
close(fd1);
	s=0;
   for(i=0;i<strlen(buf);i++)
   {
   		if(buf[i]==' ')
   		{
   			s++;
   		}
   }
   words=s+1;
   chars=strlen(buf)-s;
   fd2=open("myfifo2",O_WRONLY);
   sprintf(str, "\nNumber of spaces:%d\nNumber of words:%d\nNumber of characters:%d.",s,words,chars);
write(fd2,str,strlen(str));
close(fd2);
return 0;
}