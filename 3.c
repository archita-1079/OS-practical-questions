//write a c program to create input .txt in parent and write your name univeristy rollno. and class roll n0. in it and them read same file in child process and print the contents

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
    pid_t pid;
    char buffer[256];

    FILE *fp = fopen("input.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        exit(1);
    }

    fprintf(fp, "Name: John Doe\n");
    fprintf(fp, "University Roll No: 20261001\n");
    fprintf(fp, "Class Roll No: 45\n");
    fclose(fp);

   
    pid = fork();

    if (pid < 0) {
        printf("Fork failed!\n");
        exit(1);
    } 
    else if (pid == 0) {
        printf("--- Child Process Reading input.txt ---\n");
        
        FILE *child_fp = fopen("input.txt", "r");
        if (child_fp == NULL) {
            printf("Error opening file for reading!\n");
            exit(1);
        }

        while (fgets(buffer, sizeof(buffer), child_fp) != NULL) {
            printf("%s", buffer);
        }
        
        fclose(child_fp);
    } 
    else {
      
        wait(NULL);
    }

    return 0;
}