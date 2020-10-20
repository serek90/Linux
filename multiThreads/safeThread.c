#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BIG_NUMBER 100000000UL

volatile uint32_t counter = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *count_to_big(void* arg)
{
    for(uint32_t i = 0; i < BIG_NUMBER; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;
	pthread_mutex_unlock(&lock);
    }

    return NULL;
}


int main()
{
    pthread_t thread;

    pthread_create(&thread, NULL, count_to_big, NULL);

    count_to_big(NULL);
    pthread_join(thread, NULL);
    printf("Counter = %d \n", counter);

return 0;
}
