// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file

    uint8_t *header_buffer = malloc(sizeof(uint8_t) * HEADER_SIZE); 
    if (header_buffer == NULL)
    {
        return 1;
    }

    fread(header_buffer, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header_buffer, sizeof(uint8_t), HEADER_SIZE, output);


    // TODO: Read samples from input file and write updated data to output file
    //int16_t *sample_buffer = malloc(sizeof(int16_t));
    //    if (sample_buffer == NULL)
    //    {
    //        return 1;
    //    }
    
    int16_t sample_buffer;
    //while(sample_buffer != EOF)
    //while (! feof(input))
    while (fread(&sample_buffer, sizeof(int16_t), 1, input))
    {
        printf("sample_buffer: %i\n", sample_buffer);
        sample_buffer *= factor;
        printf("sample_buffer * factor: %i\n", sample_buffer);

        fwrite(&sample_buffer, sizeof(int16_t), 1, output);
    }
    // Free memory
    free(header_buffer);

    // Close files
    fclose(input);
    fclose(output);
    printf("Done\n");

    return 0;
}
