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



// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_cycle(int, int);
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
void lock_pairs(void)
{
    // TODO
    //Checks if makes cycle
    
    for(int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = check_cycle(pairs[i].winner,pairs[i].loser); //function is called with the values of pairs[i].winner,pairs[i].loser
  
    }
    return;
}
bool check_cycle(int won, int los) // gets the values on line 216 when it's called, ie, if winner is candidate 1 and loser is candidate 2, won and los = 1 and 2 accordingly
{   
    if(locked[los][won]) //if the winner of the pairs[i] loses from a loser then return false because it's a cycle|| for example if cand 1 loses from someone that has already lost||
    {
        return false;
    }
    else
    {
        for(int i = 0; i < candidate_count; i++) //loops through the candidates
        {
           if(locked[los][i]) //if the winner is a loser and beats candidate i, continue and check
           {
               if(locked[i][won]) //if candidate i beats the current winner then
               {
                   return check_cycle(won,i); //return the values of won and i, won = won, los = i and calls itself (recursion, duh)
               }
           }
           else if(locked[i][los])//if this is true, it means i = the candidate winner of pairs[i]
           {
               return false;
           }
          
        }
        
    }
    return true;
} 


// Print the winner of the election
void print_winner(void)
{
    // TODO
    bool source;
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
             if(locked[j][i])
             {
                 source = false;
                 break;
             }
             else
             {
                 source = true;
             }
        } 
       if(source == true)
       {
           printf("%s\n",candidates[i]);
       }
    }
    return;
}

