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

// Array of candida1es

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
void merge_sort(pair pairs[], int p, int q);
bool cycle(pair p);

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

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
// Loop over candidate list and check if *name* is the name of a candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;    // update ranks arry
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
// loop over voter's preferences (the *ranks* array)
    for (int i = 0; i < candidate_count; i++)
    {
        // loop over voter's lower-ordered preferences
        for (int j = i + 1; j < candidate_count; j++)
        {
            // increment global preferences count
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
// loop over preferences array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // if more people prefer i over j rather then the converse...
            if (preferences[i][j] > preferences[j][i])
            {
                // ... record pair i,j in the pairs array
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                // update pair count
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    merge_sort(pairs, 0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // loop over pairs array, and lock-in each pair that doesn't create a cycle
    for (int i = 0; i < pair_count; i++)
        {
            if (!(cycle(pairs[i])))
            {
                locked[pairs[i].winner][pairs[i].loser] = true;
            }
            else
            {
                locked[pairs[i].winner][pairs[i].loser] = false;
            }
            
        }
    return;
}

bool cycle(pair p)
{
    //base case
    return true;

    //recursive case
    
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

// Merge sort 
void merge_sort(pair array[], int p, int q)
{
    // Initialise variables
    int it_l = p;  // left-array iterator
    int stop_l = q / 2;  // final left-side index
    int start_r = stop_l + 1;  // initial right-side index
    int it_r = start_r;  // right-array iterator
    pair buffer[q - p + 1];
    int it_b = 0;   // buffer iterator

    // Base Case: array length = 1
    if (p == q)
    {
        return;
    }
    // Sort left side array
    merge_sort(pairs, p, stop_l);

    // Sort Right side array
    merge_sort(pairs, start_r, q);

    // Merge left & right sides

    // Loop over left-side elements, compare with current-initial right side element, and copy highest to buffer
    while ((it_l <= stop_l) || (it_r <= q)) // so long as elements remain: merge!
    {
        bool left_is_not_empty = (it_l <= stop_l);
        bool left_is_larger = (preferences[pairs[it_l].winner][pairs[it_l].loser] >= preferences[pairs[it_r].winner][pairs[it_r].loser]);
        bool right_is_empty = it_r > q;

        if ((left_is_not_empty && left_is_larger) ||
            (right_is_empty))
        {
            buffer[it_b] = pairs[it_l];
            it_b++;
            it_l++;
        }

        else
        {
            buffer[it_b] = pairs[it_r];
            it_b++;
            it_r++;
        }
    }

    // TODO
    // check this
    for (int i = p; i <= q; i++)
    {
        pairs[i] = buffer[i - p];
    }
    
    return;
}
