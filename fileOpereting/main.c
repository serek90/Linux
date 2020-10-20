#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
int fd;
fd = creat(file, 0644);
if(fd == -1) printf("dupa");

}
