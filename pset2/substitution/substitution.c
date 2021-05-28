#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    // If number of arguments are wrong
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    int n = strlen(argv[1]);

    // Check string length for number of characters
    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Loop to check each character individually
    for (int i = 0; i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // Compare subsequent characters with current character to check for duplicates
        for (int j = i + 1; j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }

    // Convert key to integer array
    int key[26];

    for (int i = 0; i < n; i++)
    {
        key[i] = (int) toupper(argv[1][i]) - (65 + i);
    }

    // Get user string input
    string s = get_string("plaintext: ");

    // Using int key to convert plaintext to ciphertext
    for (int k = 0, l = strlen(s); k < l; k++)
    {
        if (isalpha(s[k]))
        {
            int index = (int) toupper(s[k]) - 65;
            s[k] = (char)((int) s[k] + key[index]);
        }
    }
    printf("ciphertext: %s\n", s);
}