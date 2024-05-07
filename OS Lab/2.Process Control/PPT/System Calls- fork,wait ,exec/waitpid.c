/* waitpid: parent waits for a child prcess to exit. */
/*  The child runs "ls -aF /". The parent sleeps until that child is exits  */

#include <stdlib.h>	/* needed to define exit() */
#include <errno.h>	/* needed for errno */
#include <unistd.h>	/* needed for fork() and getpid() */
#include <stdio.h>
#include<sys/wait.h>	/* needed for printf() */

int
main(int argc, char **argv) {
	void child(void);	/* the child calls this */
	void parent(int pid);	/* the parent calls this */
	int pid;	/* process ID */

	switch (pid = fork()) {
	case 0:		/* a fork returns 0 to the child */
		child();
		break;

	default:	/* a fork returns a pid to the parent */
		parent(pid);
		break;

	case -1:	/* something went wrong */
		perror("fork");
		exit(1);
	}
	exit(0);
}

void child(void) {
	printf("About to run ls\n");
	execlp("ls", "ls", "-aF", "/", (char*)0);
	perror("execlp");	/* if we get here, execlp failed */
	exit(1);
}



void parent(int pid)
{
	int got_pid, status;

	while (got_pid = waitpid(pid, &status, 0))   /* go to sleep until something happens */
		if ((got_pid != -1) || (errno != EINTR)) 
			break;	/* loop only for an interrupted system call */
	if (got_pid == -1)	/* system call error */
		perror("waitpid");
	else if (WIFEXITED(status))	/* process exited normally */
		printf("child process exited with value %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))	/* child exited on a signal */
		printf("child process exited due to signal %d\n", WTERMSIG(status));
	else if (WIFSTOPPED(status))	/* child was stopped */
		printf("child process was stopped by signal %d\n", WIFSTOPPED(status));
}


/*amol@amol-Aspire-5742:~$ gcc waitpid.c
amol@amol-Aspire-5742:~$ ./a.out
About to run ls
./	core	     initrd.img.old@  mnt/   sbin/  usr/
../	dev/	     lib/	      opt/   snap/  var/
bin/	etc/	     lib64/	      proc/  srv/   vmlinuz@
boot/	home/	     lost+found/      root/  sys/   vmlinuz.old@
cdrom/	initrd.img@  media/	      run/   tmp/
child process exited with value 0
amol@amol-Aspire-5742:~$ 
*/
