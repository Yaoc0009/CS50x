#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start_pop;
    int final_pop;
    int years = 0;

    // TODO: Prompt for start size
    do
    {
        start_pop = get_int("Start size: ");
    }
    while (start_pop < 9);

    // TODO: Prompt for end size
    do
    {
        final_pop = get_int("End size: ");
    }
    while (final_pop < start_pop);

    // TODO: Calculate number of years until we reach threshold
    while (start_pop < final_pop)
    {
        // Calculate change per year
        start_pop += start_pop / 3 - start_pop / 4;
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}