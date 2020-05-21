#include "helpers.h"
#include <math.h>
#include <stdio.h>

int avg1(int height, int width, RGBTRIPLE image[height][width], int i, int j);
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
        for (int j = 0; j < width / 2; j++)
        {
           swap(&image[i][j], &image[i][width - j - 1]);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;

    int red = 0; 
    int blue = 0;
    int green = 0;
    int blurNum = 0; 
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 4);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 4);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 4);
                }
                else if (j == width - 1)
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 4);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 4);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 4);
                }
                else
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed +
                    copy[i + 1][j - 1].rgbtRed) / 6);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + 
                    copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + 
                    copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6); 
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed) / 4);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) / 4);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) / 4);
                }
                else if (j == width - 1)
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 4);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 4);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 4);
                }
                else 
                {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + 
                    copy[i - 1][j + 1].rgbtRed) / 6);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + 
                    copy[i - 1][j + 1].rgbtBlue) / 6);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + 
                    copy[i - 1][j + 1].rgbtGreen) / 6);
                }
            }
            else if (j == 0)
            {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + 
                    copy[i - 1][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + 
                    copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + 
                    copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6);
            }
            else if (j == width - 1)
            {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + 
                    copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + 
                    copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + 
                    copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6);
            }
            else 
            {
                    red = round((double)(copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + 
                    copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 9);
                    blue = round((double)(copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + 
                    copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 9);
                    green = round((double)(copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + 
                    copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 9);
            }
            reassign(height,width, image, red, blue, green, i, j);

        }
    }

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
    RGBTRIPLE copy[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    
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
                    redx = copy[i][j].rgbtRed * gx[r][c] + copy[i][j + 1].rgbtRed * gx[r][c + 1] + copy[i + 1][j].rgbtRed * gx[r + 1][c]
                            + copy[i + 1][j + 1].rgbtRed * gx[r + 1][c + 1];
                    redy = copy[i][j].rgbtRed * gy[r][c] + copy[i][j + 1].rgbtRed * gy[r][c + 1] + copy[i + 1][j].rgbtRed * gy[r + 1][c]
                            + copy[i + 1][j + 1].rgbtRed * gy[r + 1][c + 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c] + copy[i][j + 1].rgbtBlue * gx[r][c + 1] + copy[i + 1][j].rgbtBlue * gx[r + 1][c]
                            + copy[i + 1][j + 1].rgbtBlue * gx[r + 1][c + 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c] + copy[i][j + 1].rgbtBlue * gy[r][c + 1] + copy[i + 1][j].rgbtBlue * gy[r + 1][c] 
                            + copy[i + 1][j + 1].rgbtBlue * gy[r + 1][c + 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c] + copy[i][j + 1].rgbtGreen * gx[r][c + 1] + copy[i + 1][j].rgbtGreen * gx[r + 1][c] 
                            + copy[i + 1][j + 1].rgbtGreen * gx[r + 1][c + 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c] + copy[i][j + 1].rgbtGreen * gy[r][c + 1] + copy[i + 1][j].rgbtGreen * gy[r + 1][c] 
                            + copy[i + 1][j + 1].rgbtGreen * gy[r + 1][c + 1];
                }
                else if (j == width - 1)
                {
                    redx = copy[i][j].rgbtRed * gx[r][c] + copy[i][j - 1].rgbtRed * gx[r][c - 1] + copy[i + 1][j].rgbtRed * gx[r + 1][c] +
                            copy[i + 1][j - 1].rgbtRed * gx[r + 1][c - 1];
                    redy = copy[i][j].rgbtRed * gy[r][c] + copy[i][j - 1].rgbtRed * gy[r][c - 1] + copy[i + 1][j].rgbtRed * gy[r + 1][c] + 
                            copy[i + 1][j - 1].rgbtRed * gy[r + 1][c - 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c] + copy[i][j - 1].rgbtBlue * gx[r][c - 1] + copy[i + 1][j].rgbtBlue * gx[r + 1][c] + 
                            copy[i + 1][j - 1].rgbtBlue * gx[r + 1][c - 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c] + copy[i][j - 1].rgbtBlue * gy[r][c - 1] + copy[i + 1][j].rgbtBlue * gy[r + 1][c] +
                            copy[i + 1][j - 1].rgbtBlue * gy[r + 1][c - 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c] + copy[i][j - 1].rgbtGreen * gx[r][c - 1] + copy[i + 1][j].rgbtGreen * gx[r + 1][c] + 
                            copy[i + 1][j - 1].rgbtGreen * gx[r + 1][c - 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c] + copy[i][j - 1].rgbtGreen * gy[r][c - 1] + copy[i + 1][j].rgbtGreen * gy[r + 1][c] + 
                            copy[i + 1][j - 1].rgbtGreen * gy[r + 1][c - 1];
                }
                else
                {
                    redx = copy[i][j].rgbtRed * gx[r][c] + copy[i][j + 1].rgbtRed * gx[r][c + 1] + copy[i][j - 1].rgbtRed * gx[r][c - 1] + copy[i + 1][j].rgbtRed * gx[r + 1][c] + 
                            copy[i + 1][j + 1].rgbtRed * gx[r + 1][c + 1]+ copy[i + 1][j - 1].rgbtRed * gx[r + 1][c - 1];
                    redy = copy[i][j].rgbtRed * gy[r][c] + copy[i][j + 1].rgbtRed * gy[r][c + 1] + copy[i][j - 1].rgbtRed * gy[r][c - 1] + 
                            copy[i + 1][j].rgbtRed * gy[r + 1][c] + copy[i + 1][j + 1].rgbtRed * gy[r + 1][c + 1]+ copy[i + 1][j - 1].rgbtRed * gy[r + 1][c - 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c] + copy[i][j + 1].rgbtBlue * gx[r][c + 1] + copy[i][j - 1].rgbtBlue * gx[r][c - 1] + 
                            copy[i + 1][j].rgbtBlue * gx[r + 1][c] + copy[i + 1][j + 1].rgbtBlue * gx[r + 1][c + 1]+ copy[i + 1][j - 1].rgbtBlue * gx[r + 1][c - 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c] + copy[i][j + 1].rgbtBlue * gy[r][c + 1] + copy[i][j - 1].rgbtBlue * gy[r][c - 1] + 
                            copy[i + 1][j].rgbtBlue * gy[r + 1][c] + copy[i + 1][j + 1].rgbtBlue * gy[r + 1][c + 1]+ copy[i + 1][j - 1].rgbtBlue * gy[r + 1][c - 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c] + copy[i][j + 1].rgbtGreen * gx[r][c + 1] + copy[i][j - 1].rgbtGreen * gx[r][c - 1] + 
                            copy[i + 1][j].rgbtGreen * gx[r + 1][c] + copy[i + 1][j + 1].rgbtGreen * gx[r + 1][c + 1]+ copy[i + 1][j - 1].rgbtGreen * gx[r + 1][c - 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c] + copy[i][j + 1].rgbtGreen * gy[r][c + 1] + copy[i][j - 1].rgbtGreen * gy[r][c - 1] + 
                            copy[i + 1][j].rgbtGreen * gy[r + 1][c] + copy[i + 1][j + 1].rgbtGreen * gy[r + 1][c + 1]+ copy[i + 1][j - 1].rgbtGreen * gy[r + 1][c - 1];
               }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    redx = copy[i][j].rgbtRed * gx[r][c] + copy[i][j + 1].rgbtRed * gx[r][c + 1] + copy[i - 1][j].rgbtRed * gx[r - 1][c] + 
                            copy[i - 1][j + 1].rgbtRed * gx[r - 1][c + 1];
                    redy = copy[i][j].rgbtRed * gy[r][c] + copy[i][c + 1].rgbtRed * gy[r][c + 1] + copy[i - 1][j].rgbtRed * gy[r - 1][c] + 
                            copy[i - 1][j + 1].rgbtRed * gy[r - 1][c + 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c] + copy[i][j + 1].rgbtBlue * gx[r][c + 1] + copy[i - 1][j].rgbtBlue * gx[r - 1][c] +
                            copy[i - 1][j + 1].rgbtBlue * gx[r - 1][c + 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c] + copy[i][j + 1].rgbtBlue * gy[r][c + 1] + copy[i - 1][j].rgbtBlue * gy[r - 1][c] + 
                            copy[i - 1][j + 1].rgbtBlue * gy[r - 1][c + 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c] + copy[i][j + 1].rgbtGreen * gx[r][c + 1] + copy[i - 1][j].rgbtGreen * gx[r - 1][c] + 
                            copy[i - 1][j + 1].rgbtGreen * gx[r - 1][c + 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c] + copy[i][j + 1].rgbtGreen * gy[r][c + 1] + copy[i - 1][j].rgbtGreen * gy[r - 1][c] + 
                            copy[i - 1][j + 1].rgbtGreen * gy[r - 1][c + 1];
                }
                else if (j == width - 1)
                {
                    redx = copy[i][j].rgbtRed * gx[r][c] + copy[i][j - 1].rgbtRed * gx[r][c - 1] + copy[i - 1][j].rgbtRed * gx[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtRed * gx[r - 1][c - 1];
                    redy = copy[i][j].rgbtRed * gy[r][c] + copy[i][j - 1].rgbtRed * gy[r][c - 1] + copy[i - 1][j].rgbtRed * gy[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtRed * gy[r - 1][c - 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c] + copy[i][j - 1].rgbtBlue * gx[r][c - 1] + copy[i - 1][j].rgbtBlue * gx[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtBlue * gx[r - 1][c - 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c] + copy[i][j - 1].rgbtBlue * gy[r][c - 1] + copy[i - 1][j].rgbtBlue * gy[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtBlue * gy[r - 1][c - 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c] + copy[i][j - 1].rgbtGreen * gx[r][c - 1] + copy[i - 1][j].rgbtGreen * gx[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtGreen * gx[r - 1][c - 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c] + copy[i][j - 1].rgbtGreen * gy[r][c - 1] + copy[i - 1][j].rgbtGreen * gy[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtGreen * gy[r - 1][c - 1];
                }
                else 
                {
                    redx = copy[i][j].rgbtRed * gx[r][c]+ copy[i][j + 1].rgbtRed * gx[r][c + 1]+ copy[i][j - 1].rgbtRed * gx[r][c - 1]+ copy[i - 1][j].rgbtRed * gx[r - 1][c] +
                            copy[i - 1][j - 1].rgbtRed * gx[r -1][c - 1]+ copy[i - 1][j + 1].rgbtRed * gx[r - 1][c + 1];
                    redy = copy[i][j].rgbtRed * gy[r][c]+ copy[i][j + 1].rgbtRed * gy[r][c + 1]+ copy[i][j - 1].rgbtRed * gy[r][c - 1]+ copy[i - 1][j].rgbtRed * gy[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtRed * gy[r -1][c - 1]+ copy[i - 1][j + 1].rgbtRed * gy[r - 1][c + 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c]+ copy[i][j + 1].rgbtBlue* gx[r][c + 1]+ copy[i][j - 1].rgbtBlue * gx[r][c - 1]+ copy[i - 1][j].rgbtBlue * gx[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtBlue * gx[r -1][c - 1]+ copy[i - 1][j + 1].rgbtBlue * gx[r - 1][c + 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c]+ copy[i][j + 1].rgbtBlue* gy[r][c + 1]+ copy[i][j - 1].rgbtBlue * gy[r][c - 1]+ copy[i - 1][j].rgbtBlue * gy[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtBlue * gy[r -1][c - 1]+ copy[i - 1][j + 1].rgbtBlue * gy[r - 1][c + 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c]+ copy[i][j + 1].rgbtGreen * gx[r][c + 1]+ copy[i][j - 1].rgbtGreen * gx[r][c - 1]+ copy[i - 1][j].rgbtGreen * gx[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtGreen * gx[r -1][c - 1]+ copy[i - 1][j + 1].rgbtGreen * gx[r - 1][c + 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c]+ copy[i][j + 1].rgbtGreen * gy[r][c + 1]+ copy[i][j - 1].rgbtGreen * gy[r][c - 1]+ copy[i - 1][j].rgbtGreen * gy[r - 1][c] + 
                            copy[i - 1][j - 1].rgbtGreen * gy[r -1][c - 1]+ copy[i - 1][j + 1].rgbtGreen * gy[r - 1][c + 1];
                }
            }
            else if (j == 0)
            {
                    redx = copy[i][j].rgbtRed * gx[r][c] + copy[i][j + 1].rgbtRed * gx[r][c + 1] + copy[i - 1][j].rgbtRed * gx[r - 1][c] + copy[i + 1][j].rgbtRed * gx[r + 1][c] + 
                    copy[i - 1][j + 1].rgbtRed * gx[r - 1][c + 1]+ copy[i + 1][j + 1].rgbtRed * gx[r + 1][c + 1];
                    redy = copy[i][j].rgbtRed * gy[r][c] + copy[i][j + 1].rgbtRed * gy[r][c + 1] + copy[i - 1][j].rgbtRed * gy[r - 1][c] +
                    copy[i + 1][j].rgbtRed * gy[r + 1][c] + copy[i - 1][j + 1].rgbtRed * gy[r - 1][c + 1]+ copy[i + 1][j + 1].rgbtRed * gy[r + 1][c + 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c] + copy[i][j + 1].rgbtBlue * gx[r][c + 1] + copy[i - 1][j].rgbtBlue * gx[r - 1][c] +
                    copy[i + 1][j].rgbtBlue * gx[r + 1][c] + copy[i - 1][j + 1].rgbtBlue * gx[r - 1][c + 1]+ copy[i + 1][j + 1].rgbtBlue * gx[r + 1][c + 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c] + copy[i][j + 1].rgbtBlue * gy[r][c + 1] + copy[i - 1][j].rgbtBlue * gy[r - 1][c] + 
                    copy[i + 1][j].rgbtBlue * gy[r + 1][c] + copy[i - 1][j + 1].rgbtBlue * gy[r - 1][c + 1]+ copy[i + 1][j + 1].rgbtBlue * gy[r + 1][c + 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c] + copy[i][j + 1].rgbtGreen * gx[r][c + 1] + copy[i - 1][j].rgbtGreen * gx[r - 1][c] +
                    copy[i + 1][j].rgbtGreen * gx[r + 1][c] + copy[i - 1][j + 1].rgbtGreen * gx[r - 1][c + 1]+ copy[i + 1][j + 1].rgbtGreen * gx[r + 1][c + 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c] + copy[i][j + 1].rgbtGreen * gy[r][c + 1] + copy[i - 1][j].rgbtGreen * gy[r - 1][c] +
                    copy[i + 1][j].rgbtGreen * gy[r + 1][c] + copy[i - 1][j + 1].rgbtGreen * gy[r - 1][c + 1]+ copy[i + 1][j + 1].rgbtGreen * gy[r + 1][c + 1];
            }
            else if (j == width - 1)
            {
                    redx = copy[i][j].rgbtRed * gx[r][c]+ copy[i][j - 1].rgbtRed * gx[r][c - 1] + copy[i - 1][j].rgbtRed * gx[r - 1][c] + 
                    copy[i + 1][j].rgbtRed * gx[r + 1][c]+ copy[i - 1][j - 1].rgbtRed * gx[r - 1][c - 1]+ copy[i + 1][j - 1].rgbtRed * gx[r + 1][c - 1];
                    redy = copy[i][j].rgbtRed * gy[r][c]+ copy[i][j - 1].rgbtRed * gy[r][c - 1] + copy[i - 1][j].rgbtRed * gy[r - 1][c] + 
                    copy[i + 1][j].rgbtRed * gy[r + 1][c]+ copy[i - 1][j - 1].rgbtRed * gy[r - 1][c - 1]+ copy[i + 1][j - 1].rgbtRed * gy[r + 1][c - 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c]+ copy[i][j - 1].rgbtBlue * gx[r][c - 1] + copy[i - 1][j].rgbtBlue * gx[r - 1][c] +
                    copy[i + 1][j].rgbtBlue * gx[r + 1][c]+ copy[i - 1][j - 1].rgbtBlue * gx[r - 1][c - 1]+ copy[i + 1][j - 1].rgbtBlue * gx[r + 1][c - 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c]+ copy[i][j - 1].rgbtBlue * gy[r][c - 1] + copy[i - 1][j].rgbtBlue * gy[r - 1][c] + 
                    copy[i + 1][j].rgbtBlue * gy[r + 1][c]+ copy[i - 1][j - 1].rgbtBlue * gy[r - 1][c - 1]+ copy[i + 1][j - 1].rgbtBlue * gy[r + 1][c - 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c]+ copy[i][j - 1].rgbtGreen * gx[r][c - 1] + copy[i - 1][j].rgbtGreen * gx[r - 1][c] + 
                    copy[i + 1][j].rgbtGreen * gx[r + 1][c]+ copy[i - 1][j - 1].rgbtGreen * gx[r - 1][c - 1]+ copy[i + 1][j - 1].rgbtGreen * gx[r + 1][c - 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c]+ copy[i][j - 1].rgbtGreen * gy[r][c - 1] + copy[i - 1][j].rgbtGreen * gy[r - 1][c] + 
                    copy[i + 1][j].rgbtGreen * gy[r + 1][c]+ copy[i - 1][j - 1].rgbtGreen * gy[r - 1][c - 1]+ copy[i + 1][j - 1].rgbtGreen * gy[r + 1][c - 1];
            }
            else
            {
                    redx = copy[i][j].rgbtRed * gx[r][c] + copy[i - 1][j - 1].rgbtRed * gx[r - 1][c - 1] + copy[i - 1][j].rgbtRed * gx[r - 1][c] +
                    copy[i + 1][j].rgbtRed * gx[r + 1][c] + copy[i - 1][j + 1].rgbtRed * gx[r - 1][c + 1] + copy[i][j - 1].rgbtRed * gx[r][c - 1] +
                    copy[i][j + 1].rgbtRed * gx[r][c + 1] + copy[i + 1][j - 1].rgbtRed * gx[r + 1][c - 1] + copy[i + 1][j + 1].rgbtRed * gx[r + 1][c + 1];
                    redy = copy[i][j].rgbtRed * gy[r][c] + copy[i - 1][j - 1].rgbtRed * gy[r - 1][c - 1] + copy[i - 1][j].rgbtRed * gy[r - 1][c] + 
                    copy[i + 1][j].rgbtRed * gy[r + 1][c] + copy[i - 1][j + 1].rgbtRed * gy[r - 1][c + 1] + copy[i][j - 1].rgbtRed * gy[r][c - 1] + 
                    copy[i][j + 1].rgbtRed * gy[r][c + 1] + copy[i + 1][j - 1].rgbtRed * gy[r + 1][c - 1] + copy[i + 1][j + 1].rgbtRed * gy[r + 1][c + 1];
                    bluex = copy[i][j].rgbtBlue * gx[r][c] + copy[i - 1][j - 1].rgbtBlue * gx[r - 1][c - 1] + copy[i - 1][j].rgbtBlue * gx[r - 1][c] +
                    copy[i + 1][j].rgbtBlue * gx[r + 1][c] + copy[i - 1][j + 1].rgbtBlue * gx[r - 1][c + 1] + copy[i][j - 1].rgbtBlue * gx[r][c - 1] + 
                    copy[i][j + 1].rgbtBlue * gx[r][c + 1] + copy[i + 1][j - 1].rgbtBlue * gx[r + 1][c - 1] + copy[i + 1][j + 1].rgbtBlue * gx[r + 1][c + 1];
                    bluey = copy[i][j].rgbtBlue * gy[r][c] + copy[i - 1][j - 1].rgbtBlue * gy[r - 1][c - 1] + copy[i - 1][j].rgbtBlue * gy[r - 1][c] + 
                    copy[i + 1][j].rgbtBlue * gy[r + 1][c] + copy[i - 1][j + 1].rgbtBlue * gy[r - 1][c + 1] + copy[i][j - 1].rgbtBlue * gy[r][c - 1] + 
                    copy[i][j + 1].rgbtBlue * gy[r][c + 1] + copy[i + 1][j - 1].rgbtBlue * gy[r + 1][c - 1] + copy[i + 1][j + 1].rgbtBlue * gy[r + 1][c + 1];
                    greenx = copy[i][j].rgbtGreen * gx[r][c] + copy[i - 1][j - 1].rgbtGreen * gx[r - 1][c - 1] + copy[i - 1][j].rgbtGreen * gx[r - 1][c] + 
                    copy[i + 1][j].rgbtGreen * gx[r - 1][c] + copy[i - 1][j + 1].rgbtGreen * gx[r - 1][c + 1] + copy[i][j - 1].rgbtGreen * gx[r][c - 1] + 
                    copy[i][j + 1].rgbtGreen * gx[r][c + 1] + copy[i + 1][j - 1].rgbtGreen * gx[r + 1][c - 1] + copy[i + 1][j + 1].rgbtGreen * gx[r + 1][c + 1];
                    greeny = copy[i][j].rgbtGreen * gy[r][c] + copy[i - 1][j - 1].rgbtGreen * gy[r - 1][c - 1] + copy[i - 1][j].rgbtGreen * gy[r - 1][c] + 
                    copy[i + 1][j].rgbtGreen * gy[r + 1][c] + copy[i - 1][j + 1].rgbtGreen * gy[r - 1][c + 1] + copy[i][j - 1].rgbtGreen * gy[r][c - 1] + 
                    copy[i][j + 1].rgbtGreen * gy[r][c + 1] + copy[i + 1][j - 1].rgbtGreen * gy[r + 1][c - 1] + copy[i + 1][j + 1].rgbtGreen * gy[r + 1][c + 1];
            }
            redSobel = round(sqrt(pow(redx, 2) + pow(redy, 2)));
            blueSobel = round(sqrt(pow(bluex, 2) + pow(bluey, 2)));
            greenSobel = round(sqrt(pow(greenx, 2) + pow(greeny, 2)));
            reassign(height, width, image, redSobel, blueSobel, greenSobel, i, j);
            
        }
    }
    return;
}

void reassign(int height, int width, RGBTRIPLE image[height][width], int red, int blue, int green, int i, int j)
{
    if (red > 255){red = 255;}
    if (blue > 255){blue = 255; }
    if (green > 255){green = 255;}
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

int avg1(int height, int width, RGBTRIPLE image[height][width], int i, int j)
{
    int avg = round((double)(image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/3);
    return avg;
}
