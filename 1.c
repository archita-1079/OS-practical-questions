/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* 
int fibo(int n)
{
    if (n == 0 || n == 1)
        return n;

    return fibo(n - 1) + fibo(n - 2);
}
*/

int main()
{
    int n;
    printf("enter n: ");
    scanf("%d", &n);
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        pid_t pid2 = fork();
        if (pid < 0)
        {
            perror("fork child failed");
            return EXIT_FAILURE;
        }
        else if (pid2 == 0)
        {
            printf("Child Child process:\n");

            int fac = 1;
            for (int i = 1; i <= n; ++i)
            {
                fac *= i;
            }
            printf("%d\n", fac);
        }
        else
        {
            wait(NULL);
            printf("Child process:\n");

            for (int i = 0; i <= n; ++i)
            {
                printf("%d   ", fibo(i));
            }
            printf("\n");
            // printf("Child PID = %d/s", (int)getpid());
            // printf("Parent PID = %d/s", (int)getppid());
        }
    }
    else
    {
        wait(NULL);
        printf("Parent process:\n");
        int sum = 0;
        for (int i = 1; i <= n; ++i)
        {
            sum += i;
        }
        printf("%d\n", sum);
        // printf("Parent PID = %d/s", (int)getpid());
    }

    return 0;
}