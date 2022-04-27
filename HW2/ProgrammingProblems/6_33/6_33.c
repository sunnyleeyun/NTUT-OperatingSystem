#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int n = 0;
int n_thread = 0;
int point  = 0;
pthread_mutex_t mutex;

void *count(void *X)
{ 
    int i;
    srand(time(NULL));
    for (i = 0; i < n_thread; ++i)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
        if (((X * X) + (Y * Y)) <= 1)
        {
            pthread_mutex_lock(&mutex);
            point++;
            pthread_mutex_unlock(&mutex);
        }
    }
    return NULL;
}

int main()
{
    pthread_t thd1, thd2, thd3;
    pthread_mutex_init(&mutex, NULL);
    do
	{
        printf("Please enter a positive number: \n");
        scanf("%d", &n);  	
	} while (n <= 0);

    n_thread = n / 4;

    pthread_create(&thd1, NULL, &count, NULL);
    pthread_create(&thd2, NULL, &count, NULL);
    pthread_create(&thd3, NULL, &count, NULL);
    pthread_join(thd1, NULL);
    pthread_join(thd2, NULL);
    pthread_join(thd3, NULL);

    pthread_mutex_destroy(&mutex);
    
    double total_points = 4.0 * point;
    double pi = total_points / n;
    printf("Pi is : %f \n", pi);  
    return 0;
}