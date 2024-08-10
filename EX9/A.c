#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *temp_file = fopen("temp_A_output.txt", "w");
    if (temp_file == NULL) {
        perror("Failed to open temporary file for writing");
        return 1;
    }

    fprintf(temp_file, "This is the first line of file A.\n");
    fprintf(temp_file, "This is the second line of file A.\n");
    fprintf(temp_file, "This is the third line of file A.\n");

    fclose(temp_file);
    printf("Process A: Successfully wrote to temp_A_output.txt\n");

    printf("Process A: My life has reached its worthy conclusion. Goodbye.\n");

    return 0;
}
