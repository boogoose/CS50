#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;
int file_counter = 0;
int open_out_file();
void write_out_file(FILE* out_file);
//char *out_file_name = "001";
char out_file_name[8] = "000.jpeg";

FILE* out_file = NULL;  // necessary as pointer's given a reference within a funcion
 
int main(int argc, char *argv[])
{
    printf("out_file_name: %s\n", out_file_name);
    printf("out_file_name[2]: %c\n", out_file_name[2]);
    printf("out_file_name[0]: %c\n", out_file_name[0]);


    out_file_name[0] = 48;


    // Check for correct usage 
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    
    // Open in-file for reading
    char *in_file_name = argv[1];
    FILE* in_file = fopen(in_file_name, "r");
    if (in_file == NULL)
    {
        printf("%s cannot be opened for reading.\n", in_file_name);
        return 1;
    }
    open_out_file();

    // Create buffer
    BYTE *buffer = malloc(BLOCK_SIZE);
    if (buffer == NULL)
    {
        return 1;
    }
    
    // Read each block from image into buffer
    while (fread(buffer, 1, BLOCK_SIZE, in_file) == BLOCK_SIZE)    
    {
        // if jpeg-signature, close last file (if existent) and open new.
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            buffer[3] >= 0xe0 &&
            buffer[3] <= 0xef)
        {

            write_out_file(out_file);
            file_counter++;
            open_out_file();
        }

        // Write buffer to file
        fwrite(buffer, 1, BLOCK_SIZE, out_file);
    }

    // write_out_file(out_file);
    fwrite(buffer, 1, BLOCK_SIZE, out_file);

    fclose(in_file);
    fclose(out_file);
    free(buffer);

    return 0;
}

void write_out_file(FILE* outfile)
{

}

int open_out_file()
{

    // Open output file for writing

    // Generate updated out_file_name
    int counter = file_counter;
    for (int i = 0; i < 3; i ++)
    {
        out_file_name[2-i] = (counter % 10) + 48;
        counter /= 10;
    }

    out_file = fopen(out_file_name, "w");
    if (out_file == NULL)
    {
        printf("%s cannot be opened for writing.\n", out_file_name);
        return 1;
    }
    return 0;
}
