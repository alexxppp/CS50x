#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    uint8_t buffer[512];
    FILE *img = NULL;
    char filename[8];
    int count = 0;

    while (fread(buffer, sizeof(uint8_t), 512, card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
            {
                for (int i = 224; i <= 239; i++)
                {
                    if (buffer[3] == i)
                    {
                        if (img != NULL)
                        {
                            fclose(img);
                        }

                        if (count < 10)
                        {
                            sprintf(filename, "00%i.jpg", count);
                        }
                        else
                        {
                            sprintf(filename, "0%i.jpg", count);
                        }
                        img = fopen(filename, "w");
                        if (img == NULL)
                        {
                            fclose(card);
                            printf("Could not create output JPEG %s.\n", filename);
                            return 1;
                        }
                        count++;
                    }
                }
            }
        }

        if (img != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), 512, img);
        }
    }

    if (img != NULL)
    {
        fclose(img);
    }

    fclose(card);
    return 0;
}
