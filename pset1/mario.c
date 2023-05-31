#include <stdio.h>
#include <cs50.h>

int main(void){
    char ch=' ';
    int height; 
    int i;
    int j; 
    int o;
    int e;
    int f;
    // int c is for the loop of wanted gaps
    int c; 
    
    // GIVE NUMBER
    do {
        height = get_int("Put height: ");
    }
    while(height<1 || height>8  );
    
    //FOR LOOPS START
    for (i=0; i<height; i++)
    {
        for ( o=height-2; o>=i; o--)
        {
            putchar (ch);
        }
        for (j=0; j<=i; j++)
        {
            printf("#");
        }
    for(c=0; c<2; c++) {
        putchar(ch);
    }
    
       
     
        for(f=0; f<=i; f++){
          printf("#");
   }
  
  
  printf("\n");
        }
        
        
    }
