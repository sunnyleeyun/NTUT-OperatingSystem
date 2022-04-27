#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>


int n = 12;
int A[12] = {15, 39, 4, 19, 7, 0, 100, 3, 22, 8, 5, 11};
int i, j;


typedef struct Arr
{
    int low;
    int high;
} Array;


void swap(int* A, int* B)
{
    int temp = *A;
    *A = *B;
    *B = temp; 
}


void *smaller_list(void *X)
{ 
    Array* sa = X;
    
    int low = sa->low;
    int high = sa->high;

    for(i = low; i <= high; ++i){
        int temp = i;
        for (j = i; j <= high - 1; ++j)
        {
            if (A[temp] > A[j + 1])
                temp = j + 1;
        }
        swap(&A[temp], &A[i]);
    }
}


void *merge(void *X)
{ 
    int b[n];
    int left = 0;
    int right = n / 2;
    int index = 0;

    while (left < n / 2 && right < n)
    {
        if (A[left] < A[right])
        {
            b[index] = A[left]; 
            index++;
            left++;
        }
        else
        {
            b[index] = A[right];
            index++;
            right++;
        }
    }

    while (left < n / 2)
    {
        b[index] = A[left]; 
        index++;
        left++;
    }

    while (right < n) 
    {
        b[index] = A[right];
        index++;
        right++;
    }
    
    for(i = 0; i < n; ++i)
        A[i]=b[i];
}


int main()
{
    pthread_t thd1, thd2, thd3;
    Array A1;
    Array A2;

    int mid = n / 2; 
    A1.low = 0;
    A1.high = mid - 1;
    A2.low = mid;
    A2.high = n - 1; 

    pthread_create(&thd1, NULL, &smaller_list, &A1);
    pthread_create(&thd2, NULL, &smaller_list, &A2);
    pthread_join(thd1, NULL);
    pthread_join(thd2, NULL);
    pthread_create(&thd3, NULL, &merge, NULL);
    pthread_join(thd3, NULL);
    printf("The sorted array: ");
    for (i = 0; i < n; ++i)
        printf("%d ", A[i]);
    printf("\n");
}