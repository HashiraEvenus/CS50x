// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
int wordcount = 0; 
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N]; 

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    
    hash(word);
    node *cursor = table[hash(word)]; //set it in the first element of linked list
   
    while(cursor != NULL)
    {
        if(strcasecmp(cursor->word, word) == 0)
        {
            return true; 
        }
        else 
        {
            cursor = cursor -> next; 
        }
        
    }
    
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    return toupper(word[0]) - 'A' && toupper(word[1]) - 'A' && toupper(word[2]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
   
    char buffer[LENGTH + 1];
    FILE *dict = fopen(dictionary,"r"); //open file
    if(dict == NULL) // if cannot open file return error
    {
        return 1;
    }
    while((fscanf(dict,"%s",buffer))!=EOF) //read string one by one
    { 
        
        node *n = malloc(sizeof(node)); //allocate memory for node

        if( n != NULL) //checks if there is enough memory, if there is
        { 
            strcpy(n->word, buffer);
            n->next = table[hash(buffer)];
            table[hash(buffer)] = n;
            //counts the words
            wordcount++;
        } 
    }
 fclose(dict);
 return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    
        return wordcount;
    
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        
        while( cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor -> next;
            free(tmp);
        }
        if(i == N-1)
        {
            return true;
        }
    }
     
    return false;
}
