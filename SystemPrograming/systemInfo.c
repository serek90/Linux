/*
*
* Program to print system information in Linux
*
* @author: jseroczy(sere90)
*
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/utsname.h>

int main()
{
	struct utsname infoBuff;

	errno = 0; // We have to clean errno manually
	if(uname(&infoBuff))
	{
		perror("Error i soccured!");
		exit(EXIT_FAILURE);
	}

	printf("System name:    %s\n", infoBuff.sysname);
	printf("Machine type:   %s\n", infoBuff.machine);
	printf("Node name:      %s\n", infoBuff.nodename);
	printf("Kernel version: %s\n", infoBuff.version);
	printf("Release:        %s\n", infoBuff.release);

	return 0;
}
