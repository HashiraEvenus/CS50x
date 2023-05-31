#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size

    int input;

    do
    {
        printf("Put a number greater or equal to 9 \n");
        input = get_int("Start size:" );
    }
    while (input <= 8);
// TODO: Prompt for end size

int end;
  do
  {
      end = get_int("End size of lamas: ");
  }
  
while (end < input);

   
    // TODO: Calculate number of years until we reach threshold
  int years = 0;  
    
    while (input<end){
    input = input + (input / 3) - (input / 4);
    years++;
}

    
    // TODO: Print number of years
   
    printf("Years: %i", years);
}