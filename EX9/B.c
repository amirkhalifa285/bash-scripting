#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *temp_file = fopen("temp_A_output.txt", "r");
    if (temp_file == NULL) {
        perror("Failed to open temporary file for reading");
        return 1;
    }

    FILE *file_B = fopen("file_B.txt", "w");
    if (file_B == NULL) {
        perror("Failed to open file_B.txt for writing");
        fclose(temp_file); // Don't forget to close the temp file if opened
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), temp_file)) {
        fprintf(file_B, "%s", buffer); // Write to file_B.txt
        printf("Process B: %s", buffer); // Print to console
    }

    fclose(temp_file);
    fclose(file_B);

    printf("Process B: Thank you for the data, A!\n");

    return 0;
}
