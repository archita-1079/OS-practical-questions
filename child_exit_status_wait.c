#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t pid = fork();
    if (0 > pid)
    {
        print("Fork Failed");
        exit(1);
    }

    if (0 == pid)
    {
        // Child process
        printf("Child exiting with status 10\n");
        exit(10);
    }
    else
    {
        // Parent process
        wait(&status);

        if (WIFEXITED(status))
        {
            printf("Parent received exit status = %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}