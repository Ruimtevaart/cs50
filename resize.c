/**
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    float f = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    //checks if f is (0; 100]
    if (f <= 0 || f > 100)
    {
        printf("f should be greater than 0 and not greater than 100\n");
        return 5;
    }

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

    // LONG OldWidth = bi.biWidth;
    // LONG OldHeight = bi.biHeight;

    //create custom headers for outfile
    BITMAPINFOHEADER biout = bi;
    biout.biWidth = biout.biWidth * f;
    biout.biHeight = biout.biHeight * f;

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding1 = (4 - (biout.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    biout.biSizeImage = ((sizeof(RGBTRIPLE) * biout.biWidth) + padding1) * abs(biout.biHeight);
    bf.bfSize = biout.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biout, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int g = 0; g < f; g++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                int k = 0;
                while (k != f)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    k++;
                }
            }

            // skip over padding, if any
            fseek(inptr, padding1, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding1; k++)
            {
                fputc(0x00, outptr);
            }
            fseek(inptr, (- (bi.biWidth * sizeof(RGBTRIPLE) + padding)), SEEK_CUR);
        }
        fseek(inptr, (bi.biWidth * sizeof(RGBTRIPLE) + padding), SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
