#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80 // The maximum length of the command

int main(void) {
    char *args[MAX_LINE / 2 + 1]; // Command line arguments
    int should_run = 1;           // Flag to determine when to exit program

    while (should_run) {
        printf("osh>");
        fflush(stdout);

        char input[MAX_LINE];
        int background = 0; // Flag for background execution

        // Read the command from the user
        if (fgets(input, MAX_LINE, stdin) == NULL) {
            perror("fgets");
            continue;
        }

        // Remove newline character and check for background execution
        size_t length = strlen(input);
        if (length > 0 && input[length - 1] == '\n') {
            input[length - 1] = '\0';
            if (length > 1 && input[length - 2] == '&') {
                background = 1;
                input[length - 2] = '\0';
            }
        }

        // Parse the input into args array
        int arg_count = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; // Null-terminate the arguments list

        if (arg_count == 0) {
            continue; // No command entered
        }

        // Check for "exit" command
        if (strcmp(args[0], "exit") == 0) {
            should_run = 0;
            continue;
        }

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            continue;
        }

        if (pid == 0) { // Child process
            // Execute the command
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else { // Parent process
            if (!background) {
                // Wait for the child process to finish
                waitpid(pid, NULL, 0);
            }
        }
    }
    return 0;
}

