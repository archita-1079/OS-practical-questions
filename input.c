// Write a C program to create input.txt in a parent process and write your name univesity roll and class in it then read same file in child process and print the content

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    FILE *file;
    char ch;

    pid_t pid = fork();
    if (0 > pid)
    {
        printf("Fork failed");
        return 1;
    }

    if (0 < pid)
    {
        file = fopen("input.txt", "w");

        fprintf(file, "Name: Akshay\n");
        fprintf(file, "University roll number: 12345679\n");
        fprintf(file, "Class: GEU-iOS\n");

        fclose(file);

        wait(NULL);
    }
    else
    {
        file = fopen("input.txt", "r");

        printf("Contents of input.txt:\n");
        while ((ch = fgetc(file)) != EOF)
        {
            printf("%c", ch);
        }

        fclose(file);
    }

    return 0;
}