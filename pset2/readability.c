#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int POINTS[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; //points for each letter to count letters
int count_letters(string letters); 
int count_words(string letters) ;
int count_sentences(string letters);
int main(void)
{
    int i=0;
//Array for letters
    string letters[i];

    letters[i] = get_string("Text : ") ;

    int letter = count_letters(letters[i]); //shows amount of letters
    int words = count_words(letters[i]); //show amount of words
    int sentences = count_sentences(letters[i]); // amount of sentences

    float l = ((float)letter/(float)words) * 100.0 ; //equation for average letters

    float s = ((float)sentences * 100 / (float)words); //equation for average sentences

    float  index = 0.0588 * l - 0.296 * s - 15.8; //formula
    index = round(index) ;

    if (index < 1) //shows thje grade levels
    {
        printf("Before Grade 1\n");
    }
    else if(index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        
        printf(" Grade %i\n", (int)index);
    }
    
}

//Function to count letters
int count_letters(string letters)
{
    int amount = 0;

    for (int i = 0, n = strlen(letters); i < n; i++)
    {
        if (isupper(letters[i]))
        {
            amount += POINTS [ letters[i] - 'A' ];
        }
        else if (islower(letters [i]))
        {
            amount += POINTS [ letters[i] - 'a' ];
        }
    }
    return amount;
}
int count_words(string letters) //counts words
{
    int spaces = 0;
    
    for (int i = 0, n = strlen(letters); i < n; i++)
    {
        if (isspace(letters[i]) && i >= 1)  //if it finds a space
        {
            if (isspace(letters[i + 1])) //if there are more than one spaces consecutively it doesn't count them as extra words
            {
                spaces = spaces - 1;
            }
            while (i < 1)//if we put space in the beginning of sentence words remain 0 and if we put a letter after space it becomes 1 word.
            {
                spaces = 0;
            }
            spaces++;
        }
        else if (i < 0) //if no letters then words are 0
        {
            spaces = 0;
        }
        if (spaces <= 0 && i >= 0) //if no spaces and only letters words are 1
        {
            spaces = 1;
        }
    }

    int wordamount = spaces;
    return wordamount;

}


int count_sentences(string letters) //counts sentences
{
    int sentences = 0;
    char ch[3] = {'!', '?', '.'};
    for (int i = 0, n = strlen(letters); i < n; i++)
    {

        if (letters[i] == ch [0] || letters[i] == ch[1] || letters[i] == ch[2])
        {
            sentences++;
        }
    }
    return sentences;
}















