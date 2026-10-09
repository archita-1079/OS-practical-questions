#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int n;
    int pipefd[2];
    pid_t pid;
    char filename[] = "even_numbers.txt";

    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // Fork the process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {
        // --- Child Process ---
        close(pipefd[0]); // Close unused read end

        // Open file and write even numbers
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Child: Error opening file");
            exit(1);
        }

        for (int i = 0; i <= n; i += 2) {
            fprintf(file, "%d\n", i);
        }
        fclose(file);

        // Pass the filename through the pipe to the parent
        // Including the null terminator to safely pass the string
        write(pipefd[1], filename, sizeof(filename));
        close(pipefd[1]); // Close write end after writing

        exit(0);
    } else {
        // --- Parent Process ---
        close(pipefd[1]); // Close unused write end

        // Wait for the child to finish writing to the file
        wait(NULL);

        char received_filename[100];
        // Read the filename from the pipe
        read(pipefd[0], received_filename, sizeof(received_filename));
        close(pipefd[0]); // Close read end after reading

        printf("\nParent: Received filename '%s' from child.\n", received_filename);
        printf("Parent: Reading and printing file contents:\n");

        // Open the received file name and print its content
        FILE *file = fopen(received_filename, "r");
        if (file == NULL) {
            perror("Parent: Error opening file");
            return 1;
        }

        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        fclose(file);
    }

    return 0;
}
