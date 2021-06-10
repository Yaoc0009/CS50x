#include <cs50.h>
#include <stdio.h>

// Prototype
int get_positive_int(void);

int main(void)
{
    int i = get_positive_int();
    printf("%i\n", i);
}

// Prompt user for positive integer
int get_positive_int(void)
{
    int n;
    do
    {
        n = get_int("Positive Intger: ");
    }
    while (n < 1);
    return n;
}