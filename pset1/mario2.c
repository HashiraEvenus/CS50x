#include <cs50.h>
#include <stdio.h>


int main(void){
    
    //Gets the input from user
    int height;
    char ch = ' ';
 do{
 height = get_int("Height : "); 
 }
 while(height<1 || height>8);
 // Nesting for loops to make the pyramid
 // prints the amount he inserted with # characters

 
 //first loop prins the row as many times as you insert 
 //second loop is for the spaces
 //third loop  prints hash (#) as many times as you insert in each row
for (int i = 0; i < height; i++)
{
   
    for(int j=0;j<=i;j++) 
    {
        printf("#");
    }
    printf("\n");
} 
      
 }
 
 
 

 
    

