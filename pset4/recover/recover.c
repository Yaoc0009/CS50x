#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// define block size
const int BLOCK_SIZE = 512;

// define byte
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Check if we are able to open files
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // initialise value for name counter, name, destination file
    int count = 0;
    char name[8];
    FILE *output = NULL;

    // Iterate through file to find jpeg
    BYTE buffer[BLOCK_SIZE];

    while (fread(buffer, BLOCK_SIZE, 1, file))
    {
        // Identify jpeg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            // if not the first jpeg block
            if (count > 0)
            {
                fclose(output);
            }

            // create name for current jpeg
            sprintf(name, "%03d.jpg", count);

            // open destination file for jpeg
            output = fopen(name, "w");

            // increment count
            count++;
        }

        // if output exists
        if (output)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }

    // close last file
    fclose(output);

    // close input file
    fclose(file);

    return 0;
}