#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	int fd;  //return flag

	fd = open("/home/serek/programs/githubC/Linux/Linux/SystemPrograming/file.txt", O_RDONLY);

	if(fd == -1) /* error */
		printf("Blad otewierania pliku");
}
