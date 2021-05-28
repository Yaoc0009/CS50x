#include <stdio.h>
#include <cs50.h>

// Prototypes
void space(int n);
void hex(int n);

int main(void)
{
    // Tnitialize value
    int height = 0;

    // Require user input
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Generate lines of space and hex
    for (int i = 1; i <= height; i++)
    {
        space(height - i);
        hex(i);
        space(2);
        hex(i);
        printf("\n");
    }
}

// Generate space based on integer input
void space(int n)
{
    while (n > 0)
    {
        printf(" ");
        n--;
    }
}

// Generate hex based on integer input
void hex(int n)
{
    while (n > 0)
    {
        printf("#");
        n--;
    }
}