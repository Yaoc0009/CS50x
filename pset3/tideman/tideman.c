#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        // // Check vote()
        // for (int j = 0; j < candidate_count; j++)
        // {
        //     printf("%i\n", ranks[j]);
        // }

        record_preferences(ranks);
        printf("\n");
    }

    // // Check record_preferences()
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         printf("%i\n", preferences[i][j]);
    //     }
    // }

    add_pairs();

    // // Check add_pairs()
    // for (int j = 0; j < pair_count; j++)
    // {
    //         printf("%i", pairs[j].winner);
    //         printf("%i\n", pairs[j].loser);
    // }

    sort_pairs();

    // // Check sort_pairs()
    // for (int j = 0; j < pair_count; j++)
    // {
    //         printf("%i", pairs[j].winner);
    //         printf("%i\n", pairs[j].loser);
    // }

    lock_pairs();

    // // Check lock_pairs()
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         printf("%i", locked[i][j]);
    //     }
    //     printf("\n");
    // }

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Selection sort
    for (int i = 0; i < pair_count; i++)
    {
        int idx = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[idx].winner][pairs[idx].loser])
            {
                idx = j;
            }
        }
        pair tmp = pairs[i];
        pairs[i] = pairs[idx];
        pairs[idx] = tmp;
    }
    return;
}

// // Check for cycle
bool recur_lock(int winner, int loser)
{
    if (winner == loser)
    {
        return false;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner])
        {
            if (!recur_lock(i, loser))
            {
                return false;
            }
        }
    }
    return true;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (recur_lock(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int count_true[MAX];

    for (int i = 0; i < candidate_count; i++)
    {
        count_true[i] = 0;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            count_true[j] += locked[i][j];
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (count_true[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

