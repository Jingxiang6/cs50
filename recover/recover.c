// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover forensic\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

    // open input file, and print out error if it's nonreadable
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //define buffer array to store 512 bytes read each time
    BYTE buffer[512];
    //output images counter
    int k = 0;
    //output images' name
    char filename[8] = {0};
    //define a file pointer to the output images, initial is NULL
    FILE *img = NULL;
    // fread return quanity if read successfully, otherwise there is an error or EOF reached
    while (1)
    {
        size_t bytes_read = fread(buffer, sizeof(BYTE), 512, inptr);
        if (bytes_read == 0) {
            break;
        }
        // if a JPEG file start catched
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL) // if img exists, close the current one and make a new one
            {
                fclose(img);
                k ++;
            }
            sprintf(filename, "%03i.jpg", k);
            img = fopen(filename, "w");
        }
        if (img == NULL) {
            continue;
        }
        fwrite(buffer, sizeof(BYTE), bytes_read, img);
    }
    if (img != NULL) {
        fclose(img);
    }
    fclose(inptr);
    return 0;
}
