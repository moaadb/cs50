// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string word = argv[1];
        int n = strlen(word);
        char leet[n];
        for (int i = 0; i < n; i++)
        {
            switch (word[i])
            {
                case 'a':
                    leet[i] = '6';
                    printf("%c", leet[i]);
                    break;
                case 'e':
                    leet[i] = '3';
                    printf("%c", leet[i]);
                    break;
                case 'i':
                    leet[i] = '1';
                    printf("%c", leet[i]);
                    break;
                case 'o':
                    leet[i] = '0';
                    printf("%c", leet[i]);
                    break;
                default:
                    printf("%c", word[i]);
                    break;
            }
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./no-vowels word\n");
        return 1;
    }
}