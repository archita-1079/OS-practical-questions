#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();
    if (0 > pid)
    {
        printf("Fork failed");
        return 1;
    }

    if (0 == pid)
    {
        printf("Child exists.\n");
    }
    else
    {
        printf("Parent sleeping for 20 seconds.\n");
        print("Run: ps -l\n");
        sleep(20);
    }

    return 0;
}