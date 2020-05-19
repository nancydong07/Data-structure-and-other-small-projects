#include "helpers.h"
#include <math.h>
#include <stdio.h>

int avg1(int height, int width, RGBTRIPLE image[height][width], int i, int j);
int diagnolRightDownAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j);
int diagnolLeftDownAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j);
int diagnolRightUpAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j);
int diagnolLeftUpAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j);
int rightAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j);
int downAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j);
int leftAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j);
int upAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j);
void reassign(int height, int width, RGBTRIPLE image[height][width], int red, int blue, int green, int i, int j);
void swap(RGBTRIPLE *a, RGBTRIPLE *b);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = avg1(height, width, image, i, j);
            reassign(height, width, image, avg, avg, avg, i, j);
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width/2; j++)
        {
           swap(&image[i][j], &image[i][width - j -1]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
   /* int diagnolRD = 0; 
    int diagnolLD = 0; 
    int diagnolRU = 0;
    int diagnolLU = 0;
    int right = 0; 
    int left =0;
    int down = 0; 
    int up = 0;*/
    int red = 0; 
    int blue = 0;
    int green = 0;
    int blurNum = 0; 
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[height][width];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j< width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed)/4);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue)/4);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen)/4);
                }
                else if (j == width - 1)
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed)/4);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue)/4);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen)/4);
                }
                else
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed)/6);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue)/6);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen)/6); 
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed)/4);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/4);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/4);
                }
                else if (j == width - 1)
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed)/4);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue)/4);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen)/4);
                }
                else 
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed)/6);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/6);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/6);
                }
            }
            else if (j == 0)
            {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed)/6);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue)/6);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen)/6);
            }
            else if (j == width - 1)
            {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed)/6);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue)/6);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen)/6);
            }
            else 
            {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed)/9);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue)/9);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen)/9);
            }
            reassign(height,width, image, red, blue, green, i, j);

        }
    }
  /*  for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           if (i == 0)
           {
               if (j == 0)
               {
                    diagnolRD = diagnolRightDownAvg(height, width, image, i, j);
                    right = rightAvg(height, width, image, i, j);
                    down = downAvg(height, width, image, i, j);
                    avg = avg1(height, width, image, i, j);
                    blurNum = round ((diagnolRD + right + down + avg)/4);
                    reassign(height, width, image, blurNum, i, j); 
               }
               else if (j == width - 1)
               {
                    down = downAvg(height, width, image, i, j);
                    diagnolLD = diagnolLeftDownAvg(height, width, image, i, j);
                    left = leftAvg(height, width, image, i, j);
                    avg = avg1(height, width, image, i, j);
                    blurNum = round ((diagnolLD + left + down + avg)/4);
                    reassign(height, width, image, blurNum, i, j); 
               }
               else 
               {
                    diagnolRD = diagnolRightDownAvg(height, width, image, i, j);
                    right = rightAvg(height, width, image, i, j);
                    down = downAvg(height, width, image, i, j);
                    diagnolLD = diagnolLeftDownAvg(height, width, image, i, j);  
                    left = leftAvg(height, width, image, i, j);
                    avg = avg1(height, width, image, i, j);
                    blurNum = round ((diagnolLD + left + down + diagnolRD + right + avg)/6);
                    reassign(height, width, image, blurNum, i, j); 
                   
               }
           }
           else if (i == height - 1)
           {
               if (j == 0)
               {
                    up = upAvg(height, width, image, i, j);
                    right = rightAvg(height, width, image, i, j);
                    diagnolRU = diagnolRightUpAvg(height, width, image, i, j);
                    avg = avg1(height, width, image, i, j);
                    blurNum = round ((diagnolRU + up + right + avg)/4);
                    reassign(height, width, image, blurNum, i, j); 
               }
               else if (j == width - 1)
               {
                    left = leftAvg(height, width, image, i, j);
                    up = upAvg(height, width, image, i, j);
                    diagnolLU = diagnolLeftUpAvg(height, width, image, i, j);
                    avg = avg1(height, width, image, i, j);
                    blurNum = round ((diagnolLU + up + left + avg)/4);
                    reassign(height, width, image, blurNum, i, j);                     
               }
               else 
               {
                    up = upAvg(height, width, image, i, j);
                    right = rightAvg(height, width, image, i, j);
                    diagnolRU = diagnolRightUpAvg(height, width, image, i, j);
                    left = leftAvg(height, width, image, i, j);
                    diagnolLU = diagnolLeftUpAvg(height, width, image, i, j);
                    avg = avg1(height, width, image, i, j);
                    blurNum = round ((diagnolLU + up + left + right + diagnolRU + avg)/6);
                    reassign(height, width, image, blurNum, i, j);           
               }
           }
           else if (j == 0)
           {
                up = upAvg(height, width, image, i, j);
                right = rightAvg(height, width, image, i, j);
                diagnolRU = diagnolRightUpAvg(height, width, image, i, j);     
                diagnolRD = diagnolRightDownAvg(height, width, image, i, j);
                down = downAvg(height, width, image, i, j);
                avg = avg1(height, width, image, i, j);
                blurNum = round ((diagnolRU + up + right + diagnolRD + down + avg)/6);
                reassign(height, width, image, blurNum, i, j);           
           }
           else if (j == width - 1)
           {
                up = upAvg(height, width, image, i, j);
                down = downAvg(height, width, image, i, j);
                left = leftAvg(height, width, image, i, j);
                diagnolLU = diagnolLeftUpAvg(height, width, image, i, j);
                diagnolLD = diagnolLeftDownAvg(height, width, image, i, j);
                avg = avg1(height, width, image, i, j);
                blurNum = round ((diagnolLU + up + left + diagnolLD + down + avg)/6);
                reassign(height, width, image, blurNum, i, j);           
           }
           else 
           {
                up = upAvg(height, width, image, i, j);
                down = downAvg(height, width, image, i, j);
                right = rightAvg(height, width, image, i, j);
                left = leftAvg(height, width, image, i, j);
                diagnolRU = diagnolRightUpAvg(height, width, image, i, j);     
                diagnolRD = diagnolRightDownAvg(height, width, image, i, j);   
                diagnolLU = diagnolLeftUpAvg(height, width, image, i, j);
                diagnolLD = diagnolLeftDownAvg(height, width, image, i, j);    
                avg = avg1(height, width, image, i, j);
                blurNum = round ((up + down + right + left + diagnolRU + diagnolRD + diagnolLU + diagnolLD + avg)/9);
                reassign(height, width, image, blurNum, i, j);           
           }
        }
    }*/

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //compute using gx and gy matrix for each color value of the pixels neighbor and it self, total 2(9 * 3) matrix mulitplication 
    //then add each color values and that the new value to reassign 
    int redx = 0;
    int redy = 0;
    int bluex = 0;
    int bluey = 0;
    int greenx = 0; 
    int greeny = 0;
    int blueSobel = 0;
    int redSobel = 0;
    int greenSobel = 0;
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int r = 0; 
    int c = 0; 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            r = 1;
            c = 1;
            if (i == 0)
            {
                if (j == 0)
                {
                    redx = image[i][j].rgbtRed * gx[r][c] + image[i][j + 1].rgbtRed * gx[r][c + 1] + image[i + 1][j].rgbtRed * gx[r + 1][c] + image[i + 1][j + 1].rgbtRed * gx[r + 1][c + 1];
                    redy = image[i][j].rgbtRed * gy[r][c] + image[i][j + 1].rgbtRed * gy[r][c + 1] + image[i + 1][j].rgbtRed * gy[r + 1][c] + image[i + 1][j + 1].rgbtRed * gy[r + 1][c + 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c] + image[i][j + 1].rgbtBlue * gx[r][c + 1] + image[i + 1][j].rgbtBlue * gx[r + 1][c] + image[i + 1][j + 1].rgbtBlue * gx[r + 1][c + 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c] + image[i][j + 1].rgbtBlue * gy[r][c + 1] + image[i + 1][j].rgbtBlue * gy[r + 1][c] + image[i + 1][j + 1].rgbtBlue * gy[r + 1][c + 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c] + image[i][j + 1].rgbtGreen * gx[r][c + 1] + image[i + 1][j].rgbtGreen * gx[r + 1][c] + image[i + 1][j + 1].rgbtGreen * gx[r + 1][c + 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c] + image[i][j + 1].rgbtGreen * gy[r][c + 1] + image[i + 1][j].rgbtGreen * gy[r + 1][c] + image[i + 1][j + 1].rgbtGreen * gy[r + 1][c + 1];
                }
                else if (j == width - 1)
                {
                    redx = image[i][j].rgbtRed * gx[r][c] + image[i][j - 1].rgbtRed * gx[r][c - 1] + image[i + 1][j].rgbtRed * gx[r + 1][c] + image[i + 1][j - 1].rgbtRed * gx[r + 1][c - 1];
                    redy = image[i][j].rgbtRed * gy[r][c] + image[i][j - 1].rgbtRed * gy[r][c - 1] + image[i + 1][j].rgbtRed * gy[r + 1][c] + image[i + 1][j - 1].rgbtRed * gy[r + 1][c - 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c] + image[i][j - 1].rgbtBlue * gx[r][c - 1] + image[i + 1][j].rgbtBlue * gx[r + 1][c] + image[i + 1][j - 1].rgbtBlue * gx[r + 1][c - 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c] + image[i][j - 1].rgbtBlue * gy[r][c - 1] + image[i + 1][j].rgbtBlue * gy[r + 1][c] + image[i + 1][j - 1].rgbtBlue * gy[r + 1][c - 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c] + image[i][j - 1].rgbtGreen * gx[r][c - 1] + image[i + 1][j].rgbtGreen * gx[r + 1][c] + image[i + 1][j - 1].rgbtGreen * gx[r + 1][c - 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c] + image[i][j - 1].rgbtGreen * gy[r][c - 1] + image[i + 1][j].rgbtGreen * gy[r + 1][c] + image[i + 1][j - 1].rgbtGreen * gy[r + 1][c - 1];
                }
                else
                {
                    redx = image[i][j].rgbtRed * gx[r][c] + image[i][j + 1].rgbtRed * gx[r][c + 1] + image[i][j - 1].rgbtRed * gx[r][c - 1] + image[i + 1][j].rgbtRed * gx[r + 1][c] + image[i + 1][j + 1].rgbtRed * gx[r + 1][c + 1]+ image[i + 1][j - 1].rgbtRed * gx[r + 1][c - 1];
                    redy = image[i][j].rgbtRed * gy[r][c] + image[i][j + 1].rgbtRed * gy[r][c + 1] + image[i][j - 1].rgbtRed * gy[r][c - 1] + image[i + 1][j].rgbtRed * gy[r + 1][c] + image[i + 1][j + 1].rgbtRed * gy[r + 1][c + 1]+ image[i + 1][j - 1].rgbtRed * gy[r + 1][c - 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c] + image[i][j + 1].rgbtBlue * gx[r][c + 1] + image[i][j - 1].rgbtBlue * gx[r][c - 1] + image[i + 1][j].rgbtBlue * gx[r + 1][c] + image[i + 1][j + 1].rgbtBlue * gx[r + 1][c + 1]+ image[i + 1][j - 1].rgbtBlue * gx[r + 1][c - 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c] + image[i][j + 1].rgbtBlue * gy[r][c + 1] + image[i][j - 1].rgbtBlue * gy[r][c - 1] + image[i + 1][j].rgbtBlue * gy[r + 1][c] + image[i + 1][j + 1].rgbtBlue * gy[r + 1][c + 1]+ image[i + 1][j - 1].rgbtBlue * gy[r + 1][c - 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c] + image[i][j + 1].rgbtGreen * gx[r][c + 1] + image[i][j - 1].rgbtGreen * gx[r][c - 1] + image[i + 1][j].rgbtGreen * gx[r + 1][c] + image[i + 1][j + 1].rgbtGreen * gx[r + 1][c + 1]+ image[i + 1][j - 1].rgbtGreen * gx[r + 1][c - 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c] + image[i][j + 1].rgbtGreen * gy[r][c + 1] + image[i][j - 1].rgbtGreen * gy[r][c - 1] + image[i + 1][j].rgbtGreen * gy[r + 1][c] + image[i + 1][j + 1].rgbtGreen * gy[r + 1][c + 1]+ image[i + 1][j - 1].rgbtGreen * gy[r + 1][c - 1];
               }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    redx = image[i][j].rgbtRed * gx[r][c] + image[i][j + 1].rgbtRed * gx[r][c + 1] + image[i - 1][j].rgbtRed * gx[r - 1][c] + image[i - 1][j + 1].rgbtRed * gx[r - 1][c + 1];
                    redy = image[i][j].rgbtRed * gy[r][c] + image[i][c + 1].rgbtRed * gy[r][c + 1] + image[i - 1][j].rgbtRed * gy[r - 1][c] + image[i - 1][j + 1].rgbtRed * gy[r - 1][c + 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c] + image[i][j + 1].rgbtBlue * gx[r][c + 1] + image[i - 1][j].rgbtBlue * gx[r - 1][c] + image[i - 1][j + 1].rgbtBlue * gx[r - 1][c + 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c] + image[i][j + 1].rgbtBlue * gy[r][c + 1] + image[i - 1][j].rgbtBlue * gy[r - 1][c] + image[i - 1][j + 1].rgbtBlue * gy[r - 1][c + 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c] + image[i][j + 1].rgbtGreen * gx[r][c + 1] + image[i - 1][j].rgbtGreen * gx[r - 1][c] + image[i - 1][j + 1].rgbtGreen * gx[r - 1][c + 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c] + image[i][j + 1].rgbtGreen * gy[r][c + 1] + image[i - 1][j].rgbtGreen * gy[r - 1][c] + image[i - 1][j + 1].rgbtGreen * gy[r - 1][c + 1];
                }
                else if (j == width - 1)
                {
                    redx = image[i][j].rgbtRed * gx[r][c] + image[i][j - 1].rgbtRed * gx[r][c - 1] + image[i - 1][j].rgbtRed * gx[r - 1][c] + image[i - 1][j - 1].rgbtRed * gx[r - 1][c - 1];
                    redy = image[i][j].rgbtRed * gy[r][c] + image[i][j - 1].rgbtRed * gy[r][c - 1] + image[i - 1][j].rgbtRed * gy[r - 1][c] + image[i - 1][j - 1].rgbtRed * gy[r - 1][c - 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c] + image[i][j - 1].rgbtBlue * gx[r][c - 1] + image[i - 1][j].rgbtBlue * gx[r - 1][c] + image[i - 1][j - 1].rgbtBlue * gx[r - 1][c - 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c] + image[i][j - 1].rgbtBlue * gy[r][c - 1] + image[i - 1][j].rgbtBlue * gy[r - 1][c] + image[i - 1][j - 1].rgbtBlue * gy[r - 1][c - 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c] + image[i][j - 1].rgbtGreen * gx[r][c - 1] + image[i - 1][j].rgbtGreen * gx[r - 1][c] + image[i - 1][j - 1].rgbtGreen * gx[r - 1][c - 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c] + image[i][j - 1].rgbtGreen * gy[r][c - 1] + image[i - 1][j].rgbtGreen * gy[r - 1][c] + image[i - 1][j - 1].rgbtGreen * gy[r - 1][c - 1];
                }
                else 
                {
                    redx = image[i][j].rgbtRed * gx[r][c]+ image[i][j + 1].rgbtRed * gx[r][c + 1]+ image[i][j - 1].rgbtRed * gx[r][c - 1]+ image[i - 1][j].rgbtRed * gx[r - 1][c]+ image[i - 1][j - 1].rgbtRed * gx[r -1][c - 1]+ image[i - 1][j + 1].rgbtRed * gx[r - 1][c + 1];
                    redy = image[i][j].rgbtRed * gy[r][c]+ image[i][j + 1].rgbtRed * gy[r][c + 1]+ image[i][j - 1].rgbtRed * gy[r][c - 1]+ image[i - 1][j].rgbtRed * gy[r - 1][c]+ image[i - 1][j - 1].rgbtRed * gy[r -1][c - 1]+ image[i - 1][j + 1].rgbtRed * gy[r - 1][c + 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c]+ image[i][j + 1].rgbtBlue* gx[r][c + 1]+ image[i][j - 1].rgbtBlue * gx[r][c - 1]+ image[i - 1][j].rgbtBlue * gx[r - 1][c]+ image[i - 1][j - 1].rgbtBlue * gx[r -1][c - 1]+ image[i - 1][j + 1].rgbtBlue * gx[r - 1][c + 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c]+ image[i][j + 1].rgbtBlue* gy[r][c + 1]+ image[i][j - 1].rgbtBlue * gy[r][c - 1]+ image[i - 1][j].rgbtBlue * gy[r - 1][c]+ image[i - 1][j - 1].rgbtBlue * gy[r -1][c - 1]+ image[i - 1][j + 1].rgbtBlue * gy[r - 1][c + 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c]+ image[i][j + 1].rgbtGreen * gx[r][c + 1]+ image[i][j - 1].rgbtGreen * gx[r][c - 1]+ image[i - 1][j].rgbtGreen * gx[r - 1][c]+ image[i - 1][j - 1].rgbtGreen * gx[r -1][c - 1]+ image[i - 1][j + 1].rgbtGreen * gx[r - 1][c + 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c]+ image[i][j + 1].rgbtGreen * gy[r][c + 1]+ image[i][j - 1].rgbtGreen * gy[r][c - 1]+ image[i - 1][j].rgbtGreen * gy[r - 1][c]+ image[i - 1][j - 1].rgbtGreen * gy[r -1][c - 1]+ image[i - 1][j + 1].rgbtGreen * gy[r - 1][c + 1];
                }
            }
            else if (j == 0)
            {
                    redx = image[i][j].rgbtRed * gx[r][c]+ image[i][j + 1].rgbtRed * gx[r][c + 1] + image[i - 1][j].rgbtRed * gx[r - 1][c] + image[i + 1][j].rgbtRed * gx[r + 1][c] + image[i - 1][j + 1].rgbtRed * gx[r - 1][c + 1]+ image[i + 1][j + 1].rgbtRed * gx[r + 1][c + 1];
                    redy = image[i][j].rgbtRed * gy[r][c]+ image[i][j + 1].rgbtRed * gy[r][c + 1] + image[i - 1][j].rgbtRed * gy[r - 1][c] + image[i + 1][j].rgbtRed * gy[r + 1][c] + image[i - 1][j + 1].rgbtRed * gy[r - 1][c + 1]+ image[i + 1][j + 1].rgbtRed * gy[r + 1][c + 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c]+ image[i][j + 1].rgbtBlue * gx[r][c + 1] + image[i - 1][j].rgbtBlue * gx[r - 1][c] + image[i + 1][j].rgbtBlue * gx[r + 1][c] + image[i - 1][j + 1].rgbtBlue * gx[r - 1][c + 1]+ image[i + 1][j + 1].rgbtBlue * gx[r + 1][c + 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c]+ image[i][j + 1].rgbtBlue * gy[r][c + 1] + image[i - 1][j].rgbtBlue * gy[r - 1][c] + image[i + 1][j].rgbtBlue * gy[r + 1][c] + image[i - 1][j + 1].rgbtBlue * gy[r - 1][c + 1]+ image[i + 1][j + 1].rgbtBlue * gy[r + 1][c + 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c]+ image[i][j + 1].rgbtGreen * gx[r][c + 1] + image[i - 1][j].rgbtGreen * gx[r - 1][c] + image[i + 1][j].rgbtGreen * gx[r + 1][c] + image[i - 1][j + 1].rgbtGreen * gx[r - 1][c + 1]+ image[i + 1][j + 1].rgbtGreen * gx[r + 1][c + 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c]+ image[i][j + 1].rgbtGreen * gy[r][c + 1] + image[i - 1][j].rgbtGreen * gy[r - 1][c] + image[i + 1][j].rgbtGreen * gy[r + 1][c]+ image[i - 1][j + 1].rgbtGreen * gy[r - 1][c + 1]+ image[i + 1][j + 1].rgbtGreen * gy[r + 1][c + 1];
            }
            else if (j == width - 1)
            {
                    redx = image[i][j].rgbtRed * gx[r][c]+ image[i][j - 1].rgbtRed * gx[r][c - 1] + image[i - 1][j].rgbtRed * gx[r - 1][c] + image[i + 1][j].rgbtRed * gx[r + 1][c]+ image[i - 1][j - 1].rgbtRed * gx[r - 1][c - 1]+ image[i + 1][j - 1].rgbtRed * gx[r + 1][c - 1];
                    redy = image[i][j].rgbtRed * gy[r][c]+ image[i][j - 1].rgbtRed * gy[r][c - 1] + image[i - 1][j].rgbtRed * gy[r - 1][c] + image[i + 1][j].rgbtRed * gy[r + 1][c]+ image[i - 1][j - 1].rgbtRed * gy[r - 1][c - 1]+ image[i + 1][j - 1].rgbtRed * gy[r + 1][c - 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c]+ image[i][j - 1].rgbtBlue * gx[r][c - 1] + image[i - 1][j].rgbtBlue * gx[r - 1][c] + image[i + 1][j].rgbtBlue * gx[r + 1][c]+ image[i - 1][j - 1].rgbtBlue * gx[r - 1][c - 1]+ image[i + 1][j - 1].rgbtBlue * gx[r + 1][c - 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c]+ image[i][j - 1].rgbtBlue * gy[r][c - 1] + image[i - 1][j].rgbtBlue * gy[r - 1][c] + image[i + 1][j].rgbtBlue * gy[r + 1][c]+ image[i - 1][j - 1].rgbtBlue * gy[r - 1][c - 1]+ image[i + 1][j - 1].rgbtBlue * gy[r + 1][c - 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c]+ image[i][j - 1].rgbtGreen * gx[r][c - 1] + image[i - 1][j].rgbtGreen * gx[r - 1][c] + image[i + 1][j].rgbtGreen * gx[r + 1][c]+ image[i - 1][j - 1].rgbtGreen * gx[r - 1][c - 1]+ image[i + 1][j - 1].rgbtGreen * gx[r + 1][c - 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c]+ image[i][j - 1].rgbtGreen * gy[r][c - 1] + image[i - 1][j].rgbtGreen * gy[r - 1][c] + image[i + 1][j].rgbtGreen * gy[r + 1][c]+ image[i - 1][j - 1].rgbtGreen * gy[r - 1][c - 1]+ image[i + 1][j - 1].rgbtGreen * gy[r + 1][c - 1];
            }
            else
            {
                    redx = image[i][j].rgbtRed * gx[r][c] + image[i - 1][j - 1].rgbtRed * gx[r - 1][c - 1] + image[i - 1][j].rgbtRed * gx[r - 1][c] + image[i - 1][j + 1].rgbtRed * gx[r - 1][c + 1] + image[i][j - 1].rgbtRed * gx[r][c - 1] + image[i][j + 1].rgbtRed * gx[r][c + 1] + image[i + 1][j - 1].rgbtRed * gx[r + 1][c - 1] + image[i + 1][j + 1].rgbtRed * gx[r + 1][c + 1];
                    redy = image[i][j].rgbtRed * gy[r][c] + image[i - 1][j - 1].rgbtRed * gy[r - 1][c - 1] + image[i - 1][j].rgbtRed * gy[r - 1][c] + image[i - 1][j + 1].rgbtRed * gy[r - 1][c + 1] + image[i][j - 1].rgbtRed * gy[r][c - 1] + image[i][j + 1].rgbtRed * gy[r][c + 1] + image[i + 1][j - 1].rgbtRed * gy[r + 1][c - 1] + image[i + 1][j + 1].rgbtRed * gy[r + 1][c + 1];
                    bluex = image[i][j].rgbtBlue * gx[r][c] + image[i - 1][j - 1].rgbtBlue * gx[r - 1][c - 1] + image[i - 1][j].rgbtBlue * gx[r - 1][c] + image[i - 1][j + 1].rgbtBlue * gx[r - 1][c + 1] + image[i][j - 1].rgbtBlue * gx[r][c - 1] + image[i][j + 1].rgbtBlue * gx[r][c + 1] + image[i + 1][j - 1].rgbtBlue * gx[r + 1][c - 1] + image[i + 1][j + 1].rgbtBlue * gx[r + 1][c + 1];
                    bluey = image[i][j].rgbtBlue * gy[r][c] + image[i - 1][j - 1].rgbtBlue * gy[r - 1][c - 1] + image[i - 1][j].rgbtBlue * gy[r - 1][c] + image[i - 1][j + 1].rgbtBlue * gy[r - 1][c + 1] + image[i][j - 1].rgbtBlue * gy[r][c - 1] + image[i][j + 1].rgbtBlue * gy[r][c + 1] + image[i + 1][j - 1].rgbtBlue * gy[r + 1][c - 1] + image[i + 1][j + 1].rgbtBlue * gy[r + 1][c + 1];
                    greenx = image[i][j].rgbtGreen * gx[r][c] + image[i - 1][j - 1].rgbtGreen * gx[r - 1][c - 1] + image[i - 1][j].rgbtGreen * gx[r - 1][c] + image[i - 1][j + 1].rgbtGreen * gx[r - 1][c + 1] + image[i][j - 1].rgbtGreen * gx[r][c - 1] + image[i][j + 1].rgbtGreen * gx[r][c + 1] + image[i + 1][j - 1].rgbtGreen * gx[r + 1][c - 1] + image[i + 1][j + 1].rgbtGreen * gx[r + 1][c + 1];
                    greeny = image[i][j].rgbtGreen * gy[r][c] + image[i - 1][j - 1].rgbtGreen * gy[r - 1][c - 1] + image[i - 1][j].rgbtGreen * gy[r - 1][c] + image[i - 1][j + 1].rgbtGreen * gy[r - 1][c + 1] + image[i][j - 1].rgbtGreen * gy[r][c - 1] + image[i][j + 1].rgbtGreen * gy[r][c + 1] + image[i + 1][j - 1].rgbtGreen * gy[r + 1][c - 1] + image[i + 1][j + 1].rgbtGreen * gy[r + 1][c + 1];
            }
            redSobel = round(sqrt(pow(redx, 2) + pow(redy, 2)));
            printf("red is %i\n", redx);
            blueSobel = round(sqrt(pow(bluex, 2) + pow(bluey, 2)));
            greenSobel = round(sqrt(pow(greenx, 2) + pow(greeny, 2)));
            reassign(height,width, image, redSobel, blueSobel, greenSobel, i, j);
            
        }
    }
    return;
}

void reassign(int height, int width, RGBTRIPLE image[height][width], int red, int blue, int green, int i, int j)
{
     if (red > 255)
     {
         red = 255;
     }
     if (blue > 255)
     {
         blue = 255; 
     }
     if (green > 255)
     {
         green = 255;
     }
     image[i][j].rgbtRed = red;
     image[i][j].rgbtBlue = blue;
     image[i][j].rgbtGreen = green;
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE temp = *b;
    *b = *a;
    *a = temp;
}


int diagnolRightDownAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((image[i + 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtGreen)/3);
    return avg;
}

int diagnolLeftDownAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((image[i + 1][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtRed + image[i + 1][j- 1].rgbtGreen)/3);
    return avg; 
}

int diagnolRightUpAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((image[i - 1][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtRed + image[i - 1][j + 1].rgbtGreen)/3);
    return avg; 
}

int diagnolLeftUpAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtRed + image[i - 1][j- 1].rgbtGreen)/3);
    return avg; 
}

int rightAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((image[i][j + 1].rgbtBlue + image[i][j + 1].rgbtRed + image[i][j + 1].rgbtGreen)/3);
    return avg;
}

int leftAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((image[i][j - 1].rgbtBlue + image[i][j - 1].rgbtRed + image[i][j - 1].rgbtGreen)/3);
    return avg;
}

int downAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((image[i+1][j].rgbtBlue + image[i + 1][j].rgbtRed + image[i + 1][j].rgbtGreen)/3);
    return avg;
}

int upAvg(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((image[i - 1][j].rgbtBlue + image[i - 1][j].rgbtRed + image[i - 1][j].rgbtGreen)/3);
    return avg;
}

int avg1(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((double)(image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/3);
    return avg;
}
