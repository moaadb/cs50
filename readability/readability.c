#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    float letterCount = count_letters(text);
    float wordCount = count_words(text);
    float sentenceCount = count_sentences(text);
    float L = letterCount / wordCount * 100;
    float S = sentenceCount / wordCount * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    int letterCount = 0;
    int stringLength = strlen(text);

    for (int i = 0; i < stringLength; i++)
    {
        if (isalpha(text[i]))
        {
            letterCount++;
        }
    }
    return letterCount;
}

int count_words(string text)
{
    int wordCount = 0;
    int stringLength = strlen(text);

    for (int i = 0; i < stringLength; i++)
    {
        if (isspace(text[i]) || i == stringLength - 1)
        {
            wordCount++;
        }
    }
    return wordCount;
}

int count_sentences(string text)
{
    int sentenceCount = 0;
    int stringLength = strlen(text);

    for (int i = 0; i < stringLength; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentenceCount++;
        }
    }
    return sentenceCount;
}