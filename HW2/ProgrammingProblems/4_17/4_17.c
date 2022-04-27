#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int n = 0;
int point  = 0;

void *count(void *X)
{
    int i;
    srand( time(NULL) ); 
    for (i=0; i < n; ++i)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
        if (((X * X) + (Y * Y)) <= 1)
            point++;
    }
    return NULL;
}

int main()
{
    pthread_t thread;
    do
    {
        printf("Please enter a positive number: \n");
        scanf("%d", &n);  	
	} while (n <= 0);
  
    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);
    
    double total_points = 4.0 * point;
    double pi = total_points / n;
    printf("Pi is : %f \n", pi);  
    return 0;
}