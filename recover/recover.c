#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
 
 const int buff = 512;
 FILE *img = NULL;
int main(int argc, char *argv[])
{
    if( argc != 2 )
    { 
        printf("Usage : ./recover IMAGE\n");
        return 1;
    }
 FILE *f = fopen(argv[1],"r");
 uint8_t buffer[buff]; 
 char jpeg[sizeof(int16_t)] ;
 int i =0; //counter of jpg images 
 //bool first = false;
 while(fread(&buffer, sizeof(uint8_t), 512, f))
 {
     if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // if it's .jpg
     {
         if (i > 1)
         {
          fclose(img);
         }
        sprintf(jpeg, "%03i.jpg", i); //write the header of the file (e.g. 001.jpg )
        i++;
         img = fopen(jpeg, "w"); //we open a new file (the jpeg file from above) to write to it
     }
     if(i>=1)
     {
         fwrite(&buffer, sizeof(uint8_t), 512, img);
     }
     
     
 }
  
 fclose(img);
 fclose(f);
} 