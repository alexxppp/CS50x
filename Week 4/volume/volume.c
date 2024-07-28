// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;
typedef int16_t TWOBYTES;

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

    // TODO: Copy header from input file to output file
    // I got the header, which i have to fully copy in the output.wav file, without any change
    BYTE byte;
    for (int i = 0; i < 44; i++)
    {
        fread(&byte, sizeof(byte), 1, input);
        fwrite(&byte, sizeof(byte), 1, output);
    }

    // TODO: Read samples from input file and write updated data to output file
    // Then I got the samples, 2 Bytes Integers that determine some other audio circumstances.
    // I have to change each one of them by multiplying them by a given factor
    // PSEUDOCODE:
    // for i in samples.length
    // sample*factor
    // append it to output.wav
    TWOBYTES twobytes;
    int index = 0;
    while (fread(&twobytes, sizeof(twobytes), 1, input) != 0)
    {
        twobytes *= factor;
        fwrite(&twobytes, sizeof(twobytes), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
