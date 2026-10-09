#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{   
    char word[20];
    pid_t pid=fork();

    if(pid < 0)
    {
        printf("Failure to create process.");
        return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        printf("**********Child Process**********");
        printf("Enter a word - ");
        scanf("%s", word);
    }
    else
    {
        printf("**********Parent Process**********");
    }
}