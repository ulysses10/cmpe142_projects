#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	printf("Parent: Process started.\n");
	printf("Parent: Forking a child.\n");

	pid_t pid = fork();
	if( pid != 0 )
	{
		// Parent
		int status;
		printf("Parent: Waiting for child with pid %d to complete ...\n", pid);
		waitpid( pid, &status, 0);
		printf("Parent: ... terminated. \n");
	}
	else
	{
		// Child
		printf(" Child: Process started with pid %d. \n", getpid());
		printf(" child: 5 second idle:");
		
		int i;
		for ( i=5; i>0; i--)
		{
			printf("%2d", i); fflush(stdout);
			sleep(1);
		}
		printf(" terminated!\n");
	}
	return 0;
}
