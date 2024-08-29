#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define NUM_ITERATIONS 5

void spawn_process(const char* process_name, char* argv[]) {
    if (execvp(process_name, argv) == -1) {
        perror("Failed to execute process");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int pipeAB[2], pipeBA[2];
    pid_t pidA, pidB;

    if (pipe(pipeAB) == -1 || pipe(pipeBA) == -1) {
        perror("Failed to create pipes");
        exit(EXIT_FAILURE);
    }

    char pipeAB_read_fd[10], pipeAB_write_fd[10], pipeBA_read_fd[10], pipeBA_write_fd[10];
    snprintf(pipeAB_read_fd, sizeof(pipeAB_read_fd), "%d", pipeAB[0]);
    snprintf(pipeAB_write_fd, sizeof(pipeAB_write_fd), "%d", pipeAB[1]);
    snprintf(pipeBA_read_fd, sizeof(pipeBA_read_fd), "%d", pipeBA[0]);
    snprintf(pipeBA_write_fd, sizeof(pipeBA_write_fd), "%d", pipeBA[1]);

    char* argvA[] = {"A", pipeAB_read_fd, pipeBA_write_fd, NULL};
    char* argvB[] = {"B", pipeAB_write_fd, pipeBA_read_fd, NULL};

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        pidA = fork();
        if (pidA == 0) {
            close(pipeAB[1]);
            close(pipeBA[0]);
            spawn_process("./A", argvA);
        }

        pidB = fork();
        if (pidB == 0) {
            close(pipeAB[0]);
            close(pipeBA[1]);
            spawn_process("./B", argvB);
        }

        int status;
        pid_t child_pid;

        while ((child_pid = wait(&status)) > 0) {
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                if (child_pid == pidA) {
                    printf("Process A terminated, restarting...\n");
                    pidA = fork();
                    if (pidA == 0) {
                        close(pipeAB[1]);
                        close(pipeBA[0]);
                        spawn_process("./A", argvA);
                    }
                }
            }
        }

        sleep(1); // Give time for processes to settle before next iteration
    }

    close(pipeAB[0]);
    close(pipeAB[1]);
    close(pipeBA[0]);
    close(pipeBA[1]);

    return 0;
}

