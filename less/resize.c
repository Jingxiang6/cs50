// resize a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "bmp.h"

int main(int argc, char *argv[])
{
    // resize factor
    char *n = argv[1];
    // ensure proper usage
    if (argc != 4 || atoi(n) < 0 || atoi(n) > 100)
    {
        fprintf(stderr, "Usage: %s %s infile outfile\n", argv[0], argv[1]);
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create out_bi BITMAPINFOHEADER for outfile
    BITMAPINFOHEADER *out_bi = malloc(sizeof(BITMAPINFOHEADER));

    // create out_bf BITMAPFILEHEADER for outfile
    BITMAPFILEHEADER *out_bf = malloc(sizeof(BITMAPFILEHEADER));

    // assign infile structure data to outfile structure
    *out_bi = bi;
    *out_bf = bf;

    //calculate BITMAPINFOHEADER biWidth, biHeight in outfile
    out_bi->biWidth = bi.biWidth * atoi(n);
    out_bi->biHeight = bi.biHeight * atoi(n);

    // determine padding for scanlines in infile
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding for scanlines in outfile
    int out_padding = (4 - (out_bi->biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //determine biSizeImage in outfile
    out_bi->biSizeImage = (out_bi->biWidth * sizeof(RGBTRIPLE) + out_padding) * abs(out_bi->biHeight);

    //calculate BITMAPFILEHEADER bfSize
    out_bf->bfSize = out_bi->biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(out_bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(out_bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {

        // write RGB triple to outfile n times vertically
        for (int m = 0; m < atoi(n); m ++)
        {

            // skip over the first ith lines in infile
            fseek(inptr, 54 + (bi.biWidth * 3 + padding) * i, SEEK_SET);

            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);


                // write RGB triple to outfile n times
                for (int l = 0; l < atoi(n); l ++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

        // skip over padding, if any
//        fseek(inptr, padding, SEEK_CUR);

            // then add out_padding to outfile (to demonstrate how)
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    //free allocate memory
    free(out_bi);
    free(out_bf);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}