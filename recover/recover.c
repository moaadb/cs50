#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;

    BYTE signature1 = 0xff;
    BYTE signature2 = 0xd8;
    BYTE signature3 = 0xff;

    const int BLOCK_SIZE = 512;
    BYTE buffer[BLOCK_SIZE];

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("input is NULL\n");
        return 1;
    }

    char name[9];
    int indx = 0;

    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (indx == 0)
        {
            sprintf(name, "000.jpg");
        }

        if (buffer[0] == signature1 && buffer[1] == signature2 && buffer[2] == signature3)
        {
            if (indx < 10)
            {
                sprintf(name, "00%i.jpg", indx);
            }
            else
            {
                sprintf(name, "0%i.jpg", indx);
            }

            FILE *output = fopen(name, "w");
            if (output == NULL)
            {
                fclose(input);
                printf("output is NULL\n");
                return 1;
            }
            fwrite(buffer, 1, BLOCK_SIZE, output);
            fclose(output);

            indx++;
        }
        else
        {
            FILE *output = fopen(name, "a");
            if (output == NULL)
            {
                fclose(input);
                printf("output is NULL\n");
                return 1;
            }

            fwrite(buffer, 1, BLOCK_SIZE, output);
            fclose(output);
        }
    }

    fclose(input);
}