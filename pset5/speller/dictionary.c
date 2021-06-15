// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 524289;

// Hash table
node *table[N];

// Initialize size
int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // hash the word to obtain hash_value
    int hash_value = hash(word);

    // access hash_table at hash_value
    node *n = table[hash_value];

    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }

        n = n->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    // initialize sum
    long sum = 0;

    // sum ascii values of letter
    for (int i = 0; i != '\0'; i++)
    {
        sum += tolower(word[i]);
    }

    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");

    // Check if null
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Initialise word array
    char w[LENGTH + 1];

    while (fscanf(dict, "%s", w) != EOF)
    {
        // Create new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy word to node
        strcpy(n->word, w);

        // Set next to NULL
        n->next = NULL;

        // Hash word to obtain hash value
        int hash_value = hash(w);

        // Insert node into hash table at that location
        n->next = table[hash_value];
        table[hash_value] = n;
        dict_size++;
    }

    // Close file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Loop through hash_table free each node
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            // store cursor
            node *tmp2 = tmp;

            // point to next node
            tmp = tmp->next;

            // free
            free(tmp2);
        }

        if (tmp == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
