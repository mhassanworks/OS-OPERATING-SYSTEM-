#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    // Create a new process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork Failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child Process:\n");
        printf("Child PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
        // Optionally perform some tasks
        exit(0); // Child process terminates
    } else {
        // Parent process
        printf("Parent Process:\n");
        printf("Parent PID: %d\n", getpid());
        printf("Waiting for child process to finish...\n");
        wait(NULL); // Wait for the child process to complete
        printf("Child process finished.\n");
    }

    return 0;
}
