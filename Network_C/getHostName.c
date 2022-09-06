
/*
*	description:
*	Simple program that shows host name of the machine on Linux OS
*
*	@author: serek90(jseroczy)
*
*	created: 06.09.2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char hostName[BUFSIZ];

	int ret = gethostname(hostName,BUFSIZ);
	if(ret == -1)
	{
		fprintf(stderr, "Unable to get host name\n");
		exit(1);
	}


	printf("This host is: %s\n", hostName);
	return 0;
}
