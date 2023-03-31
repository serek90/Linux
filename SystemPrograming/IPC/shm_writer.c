#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define MEM_SIZE 2048
int main()
{

	/* generate unique key */
	key_t key = ftok("shm_file", 5);
	if(key == -1)
	{
		perror("ftok:");
		exit(EXIT_FAILURE);
	}

	int shm_id = shmget(key, MEM_SIZE, 0666| IPC_CREAT);
	if(shm_id == -1)
	{
		perror("shmget:");
		exit(EXIT_FAILURE);
	}

	char *str = shmat(shm_id, NULL, 0);
	if((int)str == -1)
	{
		perror("shmat:");
		exit(EXIT_FAILURE);
	}
	sprintf(str, "Hello another process");

	sleep(20);
	/* detach from shared memory */
	shmdt(str);

	/* destroy shared momory */
	shmctl(shm_id, IPC_RMID, NULL);
	return 0;
}
