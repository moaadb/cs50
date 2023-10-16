#include <cs50.h>
#include <stdio.h>

int getStartSize(void);
int getEndSize(int startSize);
int calculateGrowthTime(int n, int m);
void printAnswer(int growthTime);

int main(void)
{
    // TODO: Prompt for start size
    int startSize = getStartSize();
    // TODO: Prompt for end size
    int endSize = getEndSize(startSize);
    // TODO: Calculate number of years until we reach threshold
    if (startSize == endSize)
    {
        printAnswer(0);
    }
    else
    {
        int growthTime = calculateGrowthTime(startSize, endSize);
        printAnswer(growthTime);
    }
}

int getStartSize(void)
{
    int startSize;
    do
    {
        startSize = get_int("Starting Size: ");
    }
    while (startSize < 9);

    return startSize;
}

int getEndSize(int startSize)
{
    int endSize;
    do
    {
        endSize = get_int("Future Size: ");
    }
    while (endSize < startSize);
    return endSize;
}

void printAnswer(int growthTime)
{
    printf("Years: %i\n", growthTime);
}

int calculateGrowthTime(int n, int m)
{
    int growthTime = 0;
    do
    {
        n = n + n / 3 - n / 4;
        growthTime++;
    }
    while (n < m);
    return growthTime;
}