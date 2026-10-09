#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int n;

    print("Enter a number: ");
    scanf("%d", &n);

    pid_t pid1 = fork();
    if(0 > pid1)
    {
        printf("Fork failed");
        return 1;
    }

    if(0 == pid1)
    {
        // Child process
        printf("First child process (PID: %d)\n", getpid());
        printf("Fibonacci Series: ");

        int a = 0, b = 1, c;
        for(int i = 0; i < n; ++i)
        {
            print("%d ", a);
            c = a + b;
            a = b;
            b = c;
        }
        printf("\n");

        pid_t pid2 = fork();
        if(0 > pid2)
        {
            printf("Second fork failed");
            return 1;
        }

        if(0 == pid2)
        {
            // Second child process
            long long fact = 1;
            for(int i = 1; i <= n; ++i)
            {
                fact *= i;
            }

            print("Second child process (PID: %d)\n", getpid());
            print("Factorial of %d = %lld\n", n, fact);

            return 0;
        }
        else
        {
            wait(NULL); // Wait for second child
            return 0;
        }
    }
    else
    {
        // Original parent process
        wait(NULL);
        
        int sum = 0;
        for(int i = 1; i <= n; ++i)
        {
            sum += i;
        }

        printf("Original parent process (PID: %d)\n", getpid());
        print("Sum of first %d natural numbers = %d\n", n, sum);
    }

    return 0;
}