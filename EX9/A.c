#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int pipeAB_read_fd = atoi(argv[1]);
    int pipeBA_write_fd = atoi(argv[2]);

    FILE* fileA = fopen("fileA.txt", "r");
    if (!fileA) {
        perror("Failed to open fileA.txt");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fileA) != NULL) {
        write(pipeBA_write_fd, buffer, strlen(buffer));

        char ack[256];
        read(pipeAB_read_fd, ack, sizeof(ack));
        printf("Process A received: %s\n", ack);

        printf("My life has come to a worthy conclusion. Goodbye.\n");
        break; // Process A "commits suicide"
    }

    fclose(fileA);
    return 0;
}

