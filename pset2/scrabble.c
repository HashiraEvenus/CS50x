#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int compute_score(string word);

int main(void)
{
    
     
    // Get input words from both players
    string word[2] ;
    //for loop to get the question 2 times
    for (int i = 0; i<2; i++ )
    {
     word[i] = get_string ("Player %i :",i+1);
    
    }

    // Score both words
    int score1 = compute_score(word[0]);
    int score2 = compute_score(word[1]);
    
    if (score1>score2){
        printf ("Player 1 wins \n");
    }
    else if (score1<score2){
        printf ("Player 2 wins \n");
    }
    else
    {
        printf ("Tie");
    }
    // TODO: Print the winner
}

int compute_score(string word)
{   
    int score = 0;
    // TODO: Compute and return score for string
    for (int i = 0, n = strlen (word); i<n ; i++)
    {
        if (isupper (word[i]))
        {
        score += POINTS[word[i] - 'A'];  
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
        
    
    }
    return score; 
}

