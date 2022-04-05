#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
    int n = -1;
    while (n < 1)
    {
        printf("Please enter a positive integer: ");
        scanf("%d", &n);
    }

    int pid = fork();
    printf("Your pid is %d\n", pid);
    if (pid == -1)
    {
        printf("fork error!");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) wait(NULL);
    else // perform child process
    {
        while (n != 1)
        {
            printf("%d -> ", n);
            if (n % 2) n = 3 * n + 1; // is odd
            else n /= 2; // is even
            if (n == 1) printf("%d\n", n);
        }
    }

    return 0;
}