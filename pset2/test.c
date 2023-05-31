#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int  preferences[MAX][MAX];

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
int s=0;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_cycle(int,int);
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
    // TODO

    for(int i = 0; i < candidate_count; i++)
    {

        if (strcmp(name, candidates[i]) == 0)
        {

            ranks[rank] = i;
            rank = rank+1;
            return true;
        }
    }


    return false;
}


// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO


    for (int i = 0; i < candidate_count-1; i++)
    {
        for(int j = i+1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    int max = 0; // is a variable that helps in position of the pairs array
    // TODO
    for(int i = 0; i < candidate_count; i++) //loops through the candidates once
    {
        for(int j  = i; j < candidate_count; j++ ) //loops through the candidates a second time after i to "install" preferences
        {
        if ( preferences[i][j] > preferences[j][i]) // if more voters prefer I than J then  i is the winner and j loser.
        {
            pairs[max].winner = i;
            pairs[max].loser =j;
            max++;
            pair_count+=1;
        }
        else if (preferences[i][j] < preferences[j][i]) //If more voters prefer J than I then  J is the winner and I is the loser
        {
            pairs[max].winner = j ;

            pairs[max].loser = i ;
           max++;
            pair_count+=1;
        }
        else if (preferences[i][j] == preferences[j][i]) //if they have the same amount of victories over eacg other then they are tuied abnd the pair count does not increment
        {
            pair_count+=0;
        }
        }
    }
    return;
}
 // Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{


    for (int i = 0; i < pair_count-1; i++)
    {
         int max=i;
         int max1 = 0;
        for(int j = i+1; j < pair_count; j++)
        {

            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser] )
            {
                max = pairs[j].winner;
                max1 = pairs[j].loser;

                pairs[j].winner = pairs[i].winner;
                pairs[j].loser = pairs[i].loser;

                pairs[i].winner = max;
                pairs[i].loser = max1;

            }

        }

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void){
for (int i = 0; i < pair_count; i++)
{
    int lost = pairs[i].loser;
    for ( int j=0; j < i; j++)
    {
    int  won = pairs[j].winner;
    if(check_cycle(won,lost) == true)
    {
        locked[pairs[i].winner][pairs[i].loser] = false;
    }
    else
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }
    }
}
}

bool check_cycle (int won, int lost)
{
    if (won == lost && locked[won][pairs[won].loser] == true) 
    {
    bool cycle = true; 
    for (int c = won; c < lost; c++)
        {   
            if(locked[ pairs[c]. winner] [pairs[c].loser] == false )
            {
                cycle = false; 
                break;
            }   
            else
            {
                return true;
            }
        }
    }
    
  return false;
}
  
// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

