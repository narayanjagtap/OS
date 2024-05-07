/* b. FIFOs: Full duplex communication between two independent processes. First process accepts sentences and writes on one pipe to be read by second process and second process counts number of characters, number of words and number of lines in accepted sentences, writes this output in a text file and writes the contents of the file on second pipe to be read by first processand displays on standard output.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>


int main ()
{
	int fd1,fd2,i,j,k;
	char buf[512];

	mkfifo("myfifo1",0777);
	mkfifo("myfifo2",0777);

	printf("\nEnter the data:");
	gets(buf);
	fd1=open("myfifo1",O_WRONLY);
	write(fd1,buf,strlen(buf));
	close(fd1);
	fd2=open("myfifo2",O_RDONLY);
	read(fd2,buf,sizeof(buf));
	printf("\nData received is:");
	for(i=0;i<strlen(buf);i++)
	{
		printf("%c",buf[i]);
	}
	close(fd2);
	return 0;

} 
