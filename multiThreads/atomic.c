#include<stdio.h>
#include<stdatomic.h>
#include<pthread.h>

const int th_nb = 80;

_Atomic int acnt;
int cnt;

void *adding(void *input)
{
    for(int i=0; i<10000; i++)
        cnt++;

    pthread_exit(NULL);
}

void *adding_atomic(void *input)
{
    for(int i=0; i<10000; i++)
        acnt++;

    pthread_exit(NULL);
}

int main()
{
    time_t t1, t2, ta, tv;
    t1 = clock();
    
    pthread_t tid[th_nb];
    for(int i=0; i<th_nb; i++)
        pthread_create(&tid[i],NULL,adding_atomic,NULL);
    for(int i=0; i<th_nb; i++)
        pthread_join(tid[i],NULL);
    t2 = clock();

    printf("the value of acnt is %d\n", acnt);
    printf("Time for atomic var: %ld\n\n", ta = (t2 - t1));
    
    
    t1 = clock();
    for(int i=0; i<th_nb; i++)
        pthread_create(&tid[i],NULL,adding,NULL);
    for(int i=0; i<th_nb; i++)
        pthread_join(tid[i],NULL);
    t2 = clock();

    printf("the value of cnt is %d\n", cnt);
    printf("Time for normal var: %ld\n\n", tv = (t2 - t1));
    
    printf("Atomic/ normal time = %f\n", (float)ta/tv);
    
    
    return 0;
}
