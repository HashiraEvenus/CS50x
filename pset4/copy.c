#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main (void)
{
    char *s  = get_string("s: ");
    
    char *t = malloc(strlen(s)+1);
     if(t == NULL)
     {
         return 1;
     }
     strcpy(t,s);
     if(strlen(t) > 0)
     {
     t[0] = toupper(t[0]);
     }
    printf("s: %s\n", s);
    printf("t: %s\n", t);
    
    free(t);

    return 0;
}
//malloc = finds a chunk of memory for you to use and do whatever you want with it
//free = frees that chunk when you are done using it