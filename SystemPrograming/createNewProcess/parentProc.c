#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>



int main()
{
	printf(" Hi, I am parent process, my PID is: %d\n", getpid());
	printf("parent_proc: My parent PID is: %d\n", getppid());
        pid_t pid;

	pid = fork();
	if(pid == -1)
		perror("fork problem\n");

	/* If I am a child load differnt progam image */
	if(!pid)
	{
		const char *args[] = { "childProc", NULL};
		int ret;

		ret = execv("./childProc", args);
		if(ret == -1)
		{
			perror("execv problem");
			exit(EXIT_FAILURE);
		}
	}
	printf("parent_proc: I create a child proc: %d\n", pid); 

	int n = 5;
	while(n)
	{
		printf("Hello it's me parent process\n");
		sleep(1);
		n--;
	}
	return 0;
}
