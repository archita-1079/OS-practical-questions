#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    if (0 > pid)
    {
        printf("Fork Failed");

        return 1;
    }

    if (0 == pid)
    {
        // Child process
        print("Child Process\n");
        for (int i = 0; i <= 5; ++i)
        {
            printf("%d\n", i + 1);
        }
    }
    else
    {
        // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent process: Child has finished");
    }

    return 0;
}