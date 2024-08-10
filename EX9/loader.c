#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid_A, pid_B;

    // Fork the first child process for A
    pid_A = fork();
    if (pid_A < 0) {
        perror("Failed to fork for A");
        exit(EXIT_FAILURE);
    } else if (pid_A == 0) {
        // Inside child process A
        execl("./A", "A", NULL);
        perror("execl failed for A");
        exit(EXIT_FAILURE);
    }

    // Fork the second child process for B
    pid_B = fork();
    if (pid_B < 0) {
        perror("Failed to fork for B");
        exit(EXIT_FAILURE);
    } else if (pid_B == 0) {
        // Inside child process B
        execl("./B", "B", NULL);
        perror("execl failed for B");
        exit(EXIT_FAILURE);
    }

    // Parent process code (loader)
    printf("Loader process created children A and B with PIDs %ld and %ld.\n", (long int)pid_A, (long int)pid_B);

    // Wait for both child processes to complete
    wait(NULL);
    wait(NULL);

    return 0;
}
