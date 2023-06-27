/*
* Simple which is showing example how to use
* try_lock in c
*
* @athor: jseroczy(serek90)
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

pthread_mutex_t th_mutex;

typedef struct _thread_args
{
	int th_num;
}thread_args_t;

/**********************************************
* thread routine
**********************************************/
void *th_routine(void *args)
{
	if(!args)
		return NULL;

        thread_args_t *th_args = args;
	printf("Hello from thread %d:", th_args->th_num);
	if(!pthread_mutex_trylock(&th_mutex))
	{
		printf("I have got lock\n");
		sleep(1);
		pthread_mutex_unlock(&th_mutex);
	}
	else
	{
		printf("I haven't got lock\n");
	}
	return NULL;
}
/*********************************************
* main
*********************************************/
int main(int argc, char ** argv)
{
	const int THREAD_NUM = 8;
	pthread_t thread[THREAD_NUM];
	pthread_mutex_init(&th_mutex, NULL);
	thread_args_t th_args[THREAD_NUM];

	/* threads creation */
	for(int i = 0; i < THREAD_NUM; i++)
	{
		th_args[i].th_num = i;
		if(pthread_create(&thread[i], NULL, th_routine, &th_args[i]))
			perror("Creating thread error");
	}

	/* threads joining */
        for(int i = 0; i < THREAD_NUM; i++)
        {
                if(pthread_join(thread[i], NULL))
                        perror("Joining thread error");
        }

	return 0;
}
