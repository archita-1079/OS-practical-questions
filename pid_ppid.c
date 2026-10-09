#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (0 > pid)
    {
        // Fork failed
        printf("Fork Failed");

        return 1;
    }

    if (0 == pid)
    {
        // Child process
        printf("Child process\n");
        printf("Child PID: %d\n", getpid());
        printf("Child PPID: %d\n", getppid());
    }
    else
    {
        // Parent process
        printf("Parent process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Parent PPID: %d\n", getppid());
    }

    return 0;
}