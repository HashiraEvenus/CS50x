#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
   
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;
            float avg = (red + green + blue)/3;
             avg = round(avg); 
            image[i][j].rgbtBlue= avg;
            image[i][j].rgbtGreen = avg; 
            image[i][j].rgbtRed = avg;
        }
    } 
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    
    for(int i = 0; i < height; i++)
    {
    RGBTRIPLE pixel[width];
        
        for(int j = 0 ;j < width; j++) 
        {
            
            pixel[j] = image[i][(width-1)-j];
            
            
        }
        for(int c = 0; c < width; c++)
        {
        image[i][c] = pixel[c];
        }
        
    }
    return;
}
 
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newimage[height][width]; //create a new image to store the new values

    
    for(int i = 0; i < height; i++) //loops through height
    {
        for(int j = 0; j < width; j++) //loops through width 
        {
            float greensum = 0; // sum of GREEN  in pixels
            float bluesum = 0; // sum of BLUE color in pixels
            float redsum = 0; // sum of RED color in pixels

              int amount = 0; // amount of pixels used to divide
              
//Now we enter in the 3*3 grid to compute the average colour of pixels
            for(int k = i-1; k < i+2; k++) //makes the height of the grid
            {
                if( k < 0) //if k smaller than 0 then k becomes equals to 1 (works for k-1 in case it is less than 0)
                {
                    k = i;
                }
                for(int l = j-1; l < j+2; l++) //makes the width of the grid 
                {   
                    if(l < 0)
                    {
                        l = j;
                    }
                    float red = image[k][l].rgbtRed;
                    float blue = image[k][l].rgbtBlue;
                    float green = image[k][l].rgbtGreen;
                    
                    amount+=1;
                    redsum = redsum+red; //calculates the sum of red
                    bluesum = bluesum + blue; //calculates sum of blue
                    greensum = greensum + green; //calculates sum of green
                    if(l + 1 > width-1)
                    {
                        break;
                    }
                }
                if ( k + 1 > height-1 ) // if k exceeds the image's grid it stops looping.
                {
                    break;
                }
            }
            //assigning the RGB values of each pixel in newimage
            newimage[i][j].rgbtGreen = round(greensum/amount); 
            newimage[i][j].rgbtBlue = round(bluesum/amount);
            newimage[i][j].rgbtRed = round(redsum/amount);
            
            //TODO : Make newimage -> image
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = newimage[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newimage[height][width];
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float redsum = 0, bluesum = 0, greensum = 0;
            float redgy = 0, greengy = 0, bluegy = 0;
            int multiplier = 0;
            
            //3*3 grid is created K is height and L is width
            for(int k = i-1; k < i+2; k++ )
            {
                //if the 3*3 grid gets out of height at the beginning then it skips first column
                if( k < 0)
                {
                    k = i;
                }
                for(int l = j-1; l < j + 2; l++)
                { 
                    //if the 3*3 grid gets out of width at the beginning then it skips first column
                    if( l < 0)
                    {
                        l = j;
                    } 
                    float red = image[k][l].rgbtRed;    // counts the amount of red of a pixel
                    float blue = image[k][l].rgbtBlue;  //counts blue of pixel
                    float green = image[k][l].rgbtGreen;//counts the green of pixel
                    
                    // IF SEQUENCE TO CHANGE THE NUMBER OF MULTIPLIER INTEGER
                    if( l == j - 1 )
                    {
                        multiplier = -1;
                    }
                    else if(l == j)
                    {
                        multiplier = 0;
                    }
                    else if(l == j + 1)
                    {
                        multiplier = 1;
                    }
                    // IF SEQUENCE BUT FOR HEIGHT
                    if(k == i && l == j-1)
                    {
                        multiplier = -2;
                    }
                    else if ( k == i && l == j + 1)
                    {
                        multiplier = 2;
                    }
                       
                       redsum = redsum + (red*multiplier);
                       bluesum = bluesum + (blue*multiplier);
                       greensum = greensum + (green*multiplier);
                    
                    if ( l + 1 > height - 1 )
                    {
                        break;
                    }
                }
                if(k + 1> height - 1 )
                {
                    break;
                }
                
            }
            // G-Y GRID 
            for(int k = i - 1; k < i+2; k++)
            {
                if ( k < 0)
                {
                    k = i;
                }
                for(int l = j - 1; l < j+2; l++)
                { 
                    
                    //FIXING GRID IF L WIDTH NOT GREATER THAN 0
                    if( l < 0 )
                    {
                        l = j;
                    }
                    float red = image[k][l].rgbtRed;    // counts the amount of red of a pixel
                    float blue = image[k][l].rgbtBlue;  //counts blue of pixel
                    float green = image[k][l].rgbtGreen;//counts the green of pixel
                    
                    //PARAMETERS FOR MULTIPLIER 
                    if((l == j - 1 || l == j + 1) && k == i - 1) // WHEN IN FIRST AND LAST POSITION OF FIRST ROW IN FIRST COLUMN, MULTIPLIER IS -1
                    {
                        multiplier = -1;
                    }
                    else if(l == j && k == i-1) // IN MIDDLE POSITION OF FIRST ROW MULT = -2
                    {
                        multiplier = -2;
                    }
                    else if(k == i) //WHEN MIDDLE ROW, ALL OF POSITIONS ARE 0
                    {
                        multiplier = 0;
                    }
                    else if((l == j-1 || l == j+1 ) && k == i+1)// WHEN IN FIRST AND LAST POSITION OF LAST ROW IN LAST COLUMN, MULTIPLIER IS 1
                    {
                        multiplier = 1;
                    }
                    else if(l == j && k == i+1) //MIDDLE POSITION OF LAST ROW MULT = 2
                    {
                        multiplier = 2;
                    }
                    //FIXING GRID IF L WIDTH GREATER THAN WIDTH - 1
                    redgy = redgy + (red*multiplier);
                    bluegy = bluegy + (blue*multiplier);
                    greengy = greengy + (green*multiplier);
                    if( l + 1> width - 1)
                    {
                        break;
                    }
                    
                } //FOR L ENDS
                
                if (k + 1 > height - 1)
                {
                    break;
                }
                
            } //FOR K ENDS
            //power for red and rounding
            redgy = pow(redgy, 2);
            redsum = pow(redsum, 2);
            
            //power for green and rounding
            greengy = pow(greengy, 2);
            greensum = pow(greensum, 2);
            
            //power for blue and rounding
            bluegy = pow(bluegy, 2);
            bluesum = pow(bluesum, 2);
            
            int red = round(sqrt(redgy + redsum));
            int green = round(sqrt(greengy + greensum));
            int blue = round(sqrt(bluegy + bluesum)); 
            
            if(red > 255)
            {
                red = 255;
            }
            if(green > 255)
            {
                green =255;
            }
            if(blue > 255)
            {
                blue = 255;
            }
            newimage[i][j].rgbtRed = red;
            newimage[i][j].rgbtGreen = green;
            newimage[i][j].rgbtBlue = blue;
            
            
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = newimage[i][j];
        }
    }
    return;
}
