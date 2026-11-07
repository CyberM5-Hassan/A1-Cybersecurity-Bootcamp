
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    unsigned long line_number = 0;
    unsigned long alert_count = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <log_file> <keyword>\n",
                argv[0]);
        return 1;
    }

    file = fopen(argv[1], "r");

    if (file == NULL) {
        perror("File opening failed");
        return 1;
    }

    printf("========== LOG ANALYZER ==========\n");

    while ((length = getline(&line, &capacity, file)) != -1)
    {
        line_number++;

        if (strstr(line, argv[2]) != NULL)
        {
            alert_count++;

            printf("[ALERT] Line %lu: %s",
                   line_number, line);

            if (length > 0 && line[length - 1] != '\n')
                printf("\n");
        }
    }

    if (ferror(file)) {
        perror("Error reading file");
        free(line);
        fclose(file);
        return 1;
    }

    printf("\n========== FINAL REPORT ==========\n");
    printf("Lines scanned : %lu\n", line_number);
    printf("Alerts found  : %lu\n", alert_count);
    printf("==================================\n");

    free(line);
    fclose(file);

    return 0;
}
