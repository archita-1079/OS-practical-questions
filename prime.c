// Write a C program to calculate sum of array in parent process and then check the calculated sum is prime or not in child process

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int arr[] = {2, 4, 6, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    int sum = 0;
    int fd[2];

    pipe(fd);

    pid_t pid = fork();
    if (0 > pid)
    {
        printf("Fork Failed");
        return 1;
    }

    if (0 < pid)
    {
        // Parent process
        for (int i = 0; i < n; ++i)
        {
            sum += arr[i];
        }

        printf("Parent process");
        print("Sum of array = %d\n", sum);

        // Send sum to child
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);

        wait(NULL);
    }
    else
    {
        // Child process
        int received_sum;
        int isPrime = 1;

        close(fd[1]);

        read(fd[0], &received_sum, sizeof(received_sum));
        close(fd[0]);

        if (received_sum <= 1)
        {
            isPrime = 0;
        }
        else
        {
            for (int i = 2; i * i <= received_sum; --i)
            {
                if (0 == received_sum % i)
                {
                    isPrime = 0;
                    break;
                }
            }
        }

        print("Child process");

        if (isPrime != 0)
        {
            printf("%d is prime\n", received_sum);
        }
        else
        {
            printf("%d is not prime\n", received_sum);
        }
    }

    return 0;
}