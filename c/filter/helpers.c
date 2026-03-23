#include "helpers.h"
#include <math.h>

const float NUM = 3.0;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / NUM);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
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
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float cnt = 0.0;
            for (int rows = -1; rows <= 1; rows++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    if (i + rows >= 0 && i + rows < height && j + col >= 0 && j + col < width)
                    {
                        sumRed += copy[i + rows][j + col].rgbtRed;
                        sumGreen += copy[i + rows][j + col].rgbtGreen;
                        sumBlue += copy[i + rows][j + col].rgbtBlue;
                        cnt++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumRed / cnt);
            image[i][j].rgbtGreen = round(sumGreen / cnt);
            image[i][j].rgbtBlue = round(sumBlue / cnt);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
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
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float cnt = 0.0;
            for (int rows = -1; rows <= 1; rows++)
            {
                for (int col = -1; col <= 1; col++)
                {
                    if (i + rows >= 0 && i + rows < height && j + col >= 0 && j + col < width)
                    {
                        sumRed += copy[i + rows][j + col].rgbtRed;
                        sumGreen += copy[i + rows][j + col].rgbtGreen;
                        sumBlue += copy[i + rows][j + col].rgbtBlue;
                        cnt++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumRed / cnt);
            image[i][j].rgbtGreen = round(sumGreen / cnt);
            image[i][j].rgbtBlue = round(sumBlue / cnt);
        }
    }
    return;
}
