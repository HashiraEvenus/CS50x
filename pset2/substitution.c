#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(int argc, string argv[])
{
    //VALIDATION OF KEY
    if (argc != 2) //if there are not two arguments aka if the key is not given then it reminds to user how to use it.
    {
        printf("Usage : ./substitution KEY\n");
        return 1;
    }
        
    int count, j, i=0, n = strlen(argv[1]); //p = strlen(plaintext) ;
    char c[4] ={'.','?','!',','}  ; 
        
    if (argc == 2)
    {
        
     
        if (n == 26)
        {  
            while(argv[1][i]) //loops through all the letters and turns them to lower case
                {
                argv[1][i] = tolower(argv[1][i]);
                i++;
                }
            
            for ( i = 0; i < n; i++)
            {
                 
                
                
                count = 1; // COUNT OF LETTERS - used to check for repeated characters 
                 
                if(!isalpha(argv[1][i])) //finds if key contains only alphabetic chars and if it doesn't it stops the program
                {
                    printf("Key must contain only alphabetic characters.\n");
                    return 1;
                }
                
                for (j = i + 1; j < n; j++ ) 
                {
                    
                    if (argv[1][i] == argv[1][j] && argv[1][i] != ' ')
                    {
                    count++; 
                    argv[1][j] = '0';
                    }
                    
                    if (count > 1 && argv[1][i] !='0')
                    {   
                    printf("Key must not contain repeated characters\n");
                    return 1; 
                    }
                }
            }
            
        }
        else if (n != 26) // if n is not equal to 26  it gives error that key needs to contain 26 characters
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    //PLAINTEXT AND CIPHERTEXT
    string p = get_string ("Plaintext : ");
    int n1 = strlen(p); //string length of plaintext
    printf("ciphertext: ");
    for (i = 0; i < n1; i++)
    {
         
        if (isspace(p[i]) || p[i] == c[0] || p[i] == c[1] || p[i] == c[2] || p[i] == c[3] || !isalpha(p[i])) //If character is space or ?, .,!, comma it types it normally.
        {
            printf("%c",p[i]); 
        } 
        
        if(islower(p[i])) //if character in plaintext is lowercase it is printed in lowercase
        {
            p[i] = p[i] - 'a' ;
            int l = p[i];
            printf("%c", tolower(argv[1][l]));
        }
        
        
        else if(isupper(p[i])) //if character is uppercase it is printed in uppercase
        {
            p[i] = p[i] - 'A' ;
            int l = p[i];
            printf("%c", toupper(argv[1][l]));
        }
        
        
        
        
    }
     printf("\n");
    return 0; 
   
    
    
}
//INPUT OF USER
// string input = get_string ("Hey ");
    
    


