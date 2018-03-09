#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid amount of command line arguements, stopping program...\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File does not exist.\n");
        return 2;
    }
    unsigned char buffer[512];
    char filename[8];
    int i = 0;
    FILE *img = NULL;
    while (fread(buffer, 512, 1, file))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(filename, "%03d.jpg", i++);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(file);
                printf("Could not create %s.\n", filename);
                return 3;
            }
        }
        if (img != NULL)
        {
            int k = fwrite(buffer, 512, 1, img);
            if (k != 1)
            {
                fclose(img);
                fclose(file);
            }
        }
    }
    if (img != NULL)
    {
        fclose(img);
        fclose(file);
    }
    return 0;
}