#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int processID, parentProcID;
	processID = getpid();
	parentProcID = getppid();

	printf("PROCESS ID:\t %d\n", processID);
	printf("PARENT PROCESS ID: %d\n", parentProcID);

	return 0;
}
