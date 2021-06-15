#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Use malloc to allocate enough space for an array with 3 integers
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    // Set the values in our array
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Now if we want to store another value, we can allocate more memory
    int *tmp = malloc(4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    // Copy list of size 3 into list of size 4
    for (int i = 0; i < 3; i++)
    {
        tmp[i] = list[i];
    }

    // Add new number to list of size 4
    tmp[3] = 4;

    // Free original list of size 3
    free(list);

    // Remember new list of size 4
    list = tmp;

    // Print list
    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    // Free new list
    free(list);
}