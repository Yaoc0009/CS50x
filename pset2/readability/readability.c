#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    int count[3] = {0, 1, 0};
    // Get string input
    string s = get_string("Text: ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Count letters by checking if its one of the letters
        if (tolower(s[i]) >= 'a' && tolower(s[i]) <= 'z')
        {
            count[0] += 1;
        }
        // Count words by counting spaces
        if (s[i] == ' ')
        {
            count[1] += 1;
        }
        // Count sentences by counting ".!?"
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            count[2] += 1;
        }
    }
    // Compute Coleman-Liau index
    float L = (float) count[0] / count[1] * 100;
    float S = (float) count[2] / count[1] * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Output
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