#include <cs50.h>
#include <stdio.h>

int collatz(int number);

int main(void)
{
    int number = 0;
    do
    {
        number = get_int("Number: ");
    }
    while (number <= 0);

    return collatz(number);
}

int collatz(int number)
{
    int n = number;
    printf("%i\n", n);
    if (n == 1)
    {
        return n;
    }
    else if (n % 2)
    {
        return collatz(3 * n + 1);
    }
    else
    {
        return collatz(n / 2);
    }
}
