#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define TH_NUM 2 

int buffer[10];
int count = 0;
sem_t mutex;
sem_t empty;
sem_t full;


void* producer(void *X) 
{
    int j;
    for(j = 0; j < 1000; ++j)
    {
        int x = rand() % 1000;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[count++] = x;
        sem_post(&mutex);
        sem_post(&full);
        printf("Send %d \n", x);
    }
}


void* consumer(void *X)
{
    int j;
    for(j = 0; j < 1000; ++j)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        int y = buffer[count--];
        sem_post(&mutex);
        sem_post(&empty);
        printf("Got %d \n", y);
    }
}


int main(int argc, char const *argv[])
{
    srand(time(NULL));
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    pthread_t th[TH_NUM];
    int i;
    for (i = 0; i < TH_NUM; ++i)
    {
        i % 2 ? 
        pthread_create(&th[i], NULL, &consumer, NULL) : 
        pthread_create(&th[i], NULL, &producer, NULL);
    }

    for (i = 0; i < TH_NUM; ++i)
        pthread_join(th[i], NULL);
    
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}
