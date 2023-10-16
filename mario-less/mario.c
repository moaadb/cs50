#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_pyramid(int size);

int main(void)
{
    int n = get_size();
    print_pyramid(n);
}

int get_size(void)
{
    int size;
    do
    {
        size = get_int("Height: ");
    }
    while (size < 1 || size > 8);
    return size;
}

void print_pyramid(int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int k = size - i; k > 1; k--)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}