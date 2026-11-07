
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 16

int main(int argc, char *argv[])
{
    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;
    unsigned long offset = 0;

    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // Open file in binary read mode
    FILE *file = fopen(argv[1], "rb");

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    printf("\nOffset          Hexadecimal Data                          ASCII\n");
    printf("--------------------------------------------------------------------------\n");

    // Read file in chunks of 16 bytes
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        // Print offset
        printf("%08lX   ", offset);

        // Print hexadecimal values
        for (size_t i = 0; i < BUFFER_SIZE; i++)
        {
            if (i < bytesRead)
                printf("%02X ", buffer[i]);
            else
                printf("   ");
        }

        printf(" ");

        // Print ASCII representation
        for (size_t i = 0; i < bytesRead; i++)
        {
            if (buffer[i] >= 32 && buffer[i] <= 126)
                printf("%c", buffer[i]);
            else
                printf(".");
        }

        printf("\n");

        offset += bytesRead;
    }

    // Check for file reading errors
    if (ferror(file))
    {
        perror("Error reading file");
        fclose(file);
        return 1;
    }

    // Close file
    fclose(file);

    printf("\nFile analysis completed successfully.\n");

    return 0;
}
