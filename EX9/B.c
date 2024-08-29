#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int pipeAB_write_fd = atoi(argv[1]);
    int pipeBA_read_fd = atoi(argv[2]);

    FILE* fileB = fopen("fileB.txt", "a");
    if (!fileB) {
        perror("Failed to open fileB.txt");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    read(pipeBA_read_fd, buffer, sizeof(buffer));
    fprintf(fileB, "%s", buffer);
    printf("Process B: %s", buffer);
    fflush(fileB);

    char* ack = "Thank you for the information, I received it.";
    write(pipeAB_write_fd, ack, strlen(ack) + 1);

    fclose(fileB);
    return 0;
}

