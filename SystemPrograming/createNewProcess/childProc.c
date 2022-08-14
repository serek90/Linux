#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>



int main()
{
	printf("Hi I am child process, nice to meet you\n");
	printf("child_proc: My PID is: %d\n", getpid());
	printf("child_proc: My parent PID is: %d\n", getppid());

	int n = 5;
	while(n)
	{
		printf("Hi, it's me, child process\n");
		sleep(1);
		n--;
	}
	return 0;
}
