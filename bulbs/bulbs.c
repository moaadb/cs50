#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);
int convert_character(int decimal);

int main(void)
{

    string message = get_string("Message: ");
    int n = strlen(message);

    // loop n times, letter by letter
    for (int i = 0; i < n; i++)
    {
        float decimal = message[i];
        decimal = decimal / pow(2, 7);

        // loop 8 times, bit by bit...
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            int bit = 0;

            // convert the first letter to a binary bit
            bit = convert_character(decimal);
            print_bulb(bit);

            decimal = decimal * 2;
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

int convert_character(int decimal)
{
    int bit = 0;

    if (decimal % 2)
    {
        bit = 1;
    }
    else
    {
        bit = 0;
    }

    return bit;
}
