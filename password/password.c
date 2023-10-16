// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool hasLower = false;
    bool hasUpper = false;
    bool hasNumber = false;
    bool hasSymbol = false;

    int n = strlen(password);

    for (int i = 0; i < n; i++)
    {
        if (!isspace(password[i]))
        {
            if (islower(password[i]))
            {
                hasLower = true;
            }
            else if (isupper(password[i]))
            {
                hasUpper = true;
            }
            else if (isalnum(password[i]))
            {
                hasNumber = true;
            }
            else
            {
                hasSymbol = true;
            }
        }
    }

    if (hasLower && hasUpper && hasNumber && hasSymbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}
