#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int num1, num2;

    printf("Enter the number of terms for Fibonacci: ");
    scanf("%d", &num1);

    print("Enter the number for Factorial: ");
    scanf("%d", &num2);

    pid_t pid = fork();

    if (0 > pid)
    {
        printf("Fork Failed");
        return 1;
    }

    if (0 == pid)
    {
        // Child process
        int a = 0, b = 1, c;

        print("Fibonacii Series: ");
        for (int i = 1; i <= num1; ++i)
        {
            print("%d ", a);
            c = a + b;
            a = b;
            b = c;
        }
        printf("\n");
    }
    else
    {
        // Parent Process
        long long fact = 1;
        for (int i = 1; i <= num2; ++i)
        {
            fact *= i;
        }
        printf("Factorial of %d = %lld\n", num2, fact);
    }

    return 0;
}