/*
*	title: Example of using pipe()
*
*	author: jseroczy
*/

#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <errno.h>
#include <stdlib.h>

#define MSG_SIZE 16
char *msg_tab[] = {"Message 1!", "Message 2!", "Message 3!", "Message 4!", "Message 5!"};


int main()
{
	char inBuff[MSG_SIZE];
	int pipefds[2];

	if(pipe(pipefds) < 0)
	{
		perror("pipe open error");
		exit(EXIT_FAILURE);
	}

	int pid;
	int nBytes;
	if((pid = fork()) > 0) /* parent process */
	{
		for(int i = 0; i < (sizeof(msg_tab)/sizeof(char*)); i++)
		{
			write(pipefds[1], msg_tab[i],  MSG_SIZE);
			sleep(1);
		}
		sleep(5);
	}
	else /* child process */
	{
		printf("Hello from child process\n");
		while((nBytes = read(pipefds[0], inBuff, MSG_SIZE)) > 0)
			printf("I received: %s\n", inBuff);

		if(nBytes != 0)
			exit(1);

		printf("Finish reading from pipe\n");
	}

	return 0;
}
