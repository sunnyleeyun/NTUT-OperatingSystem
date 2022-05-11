#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGES_CNT 12

int numberOfFrames = -1;
int pages[PAGES_CNT];

int FIFO()
{
    int *frames = (int *)malloc(sizeof(int) * numberOfFrames);
    int i, j;
    for (i = 0; i < numberOfFrames; ++i)
        frames[i] = -1;
    
    int fault = 0, ptr = 0;
    for (i = 0; i < PAGES_CNT; ++i)
    {
        int find = 0;
        for (j = 0; j < numberOfFrames; ++j)
        {
            if (pages[i] == frames[j]) 
            {
                find = 1;
                break;
            }
        }
        if (!find)
        {
            frames[ptr] = pages[i];
            fault++;
            ptr = (++ptr) % numberOfFrames;
        }
    }
    free(frames);
    return fault;
}

int LRU()
{
    int *frames = (int *)malloc(sizeof(int) * numberOfFrames);
    int* framesCounter = (int *)malloc(sizeof(int) * numberOfFrames);
    int i, j, k;
    for (i = 0; i < numberOfFrames; ++i)
    {
        frames[i] = -1;
        framesCounter[i] = -1;
    }

    int fault = 0;
    for (i = 0; i < PAGES_CNT; ++i)
    {
        int find = 0;
        for (j = 0; j < numberOfFrames; ++j)
        {
            if (pages[i] == frames[j]) 
            {
                find = 1;
                framesCounter[j] = i;
                break;
            }
        }
        if (!find)
        {
            for (j = 0; j < numberOfFrames; ++j)
            {
                framesCounter[j] = frames[j] == -1 ? PAGES_CNT + 1 : PAGES_CNT;
            }
            for (j = 0; j < numberOfFrames; ++j)
            {
                for (k = i + 1; k < PAGES_CNT; ++k)
                {
                    if (frames[j] == pages[k])
                    {
                        framesCounter[j] = k;
                        break;
                    }
                }
            }

            int ptr = 0, mst = 0;
            for (j = 0; j < numberOfFrames; ++j)
            {
                if (framesCounter[j] > mst)
                {
                    mst = framesCounter[j];
                    ptr = j;
                }
            }
            frames[ptr] = pages[i];
            fault++;
        }
    }

    free(frames);
    free(framesCounter);
    return fault;
}

int OPTIMAL()
{
    int *frames = (int *)malloc(sizeof(int) * numberOfFrames);
    int* framesCounter = (int *)malloc(sizeof(int) * numberOfFrames);
    int i, j;
    for (i = 0; i < numberOfFrames; ++i)
    {
        frames[i] = -1;
        framesCounter[i] = -1;
    }

    int fault = 0;
    for (i = 0; i < PAGES_CNT; ++i)
    {
        int find = 0;
        for (j = 0; j < numberOfFrames; ++j)
        {
            if (pages[i] == frames[j]) 
            {
                find = 1;
                break;
            }
        }
        if (!find)
        {
            int lst = i, ptr = 0;
            for (j = 0; j < numberOfFrames; ++j)
            {
                if (framesCounter[j] < lst)
                {
                    lst = framesCounter[j];
                    ptr = j;
                } 
            }
            frames[ptr] = pages[i];
            fault++;
            ptr = (++ptr) % numberOfFrames;
        }
    }

    free(frames);
    free(framesCounter);
    return fault;
}

int main()
{
    while(numberOfFrames <= 0 || numberOfFrames > 7){
        printf("Please enter a number of frame between 1 ~ 7: ");
        scanf("%d", &numberOfFrames);
    }

    srand(time(NULL));
    int i;

    printf("The random page reference is: ");
    for (i = 0; i < PAGES_CNT; ++i)
    {
        pages[i] = rand() % 10; /* problem defines page from 0 ~ 9*/
        printf("%d ", pages[i]);
    }
    printf("\n");

	printf("FIFO page fault = %d\n", FIFO());
	printf("LRU page fault = %d\n", LRU());
	printf("OPTIMAL page fault = %d\n", OPTIMAL());


    return 0;
}