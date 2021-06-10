#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average
            float grey_value = round(((float) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);

            image[i][j].rgbtBlue = grey_value;
            image[i][j].rgbtGreen = grey_value;
            image[i][j].rgbtRed = grey_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temp pixel
    RGBTRIPLE tmp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Store value in temp
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // initialise temp array
    RGBTRIPLE tmp[height][width];

    int blueSum;
    int greenSum;
    int redSum;
    float count;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blueSum = 0;
            greenSum = 0;
            redSum = 0;
            count = 0.0;

            // Loop to get the values to sum together
            for (int m = -1; m <= 1; m++)
            {
                if (i + m < 0 || i + m > width - 1)
                {
                    continue;
                }

                for (int n = -1; n <= 1; n++)
                {
                    if (j + n < 0 || j + n > width - 1)
                    {
                        continue;
                    }

                    blueSum += image[i + m][j + n].rgbtBlue;
                    greenSum += image[i + m][j + n].rgbtGreen;
                    redSum += image[i + m][j + n].rgbtRed;
                    count++;
                }
            }

            tmp[i][j].rgbtBlue = round(blueSum / count);
            tmp[i][j].rgbtGreen = round(greenSum / count);
            tmp[i][j].rgbtRed = round(redSum / count);
        }
    }

    // Copy array to original array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // initialise temp array
    RGBTRIPLE tmp[height][width];

    // Sobel operators
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store respective Gx, Gy values in array
            float blueSum[2] = {0.0, 0.0};
            float greenSum[2] = {0.0, 0.0};
            float redSum[2] = {0.0, 0.0};

            // Loop to get the values to sum together
            for (int m = -1; m <= 1; m++)
            {
                if (i + m < 0 || i + m > width - 1)
                {
                    continue;
                }

                for (int n = -1; n <= 1; n++)
                {
                    if (j + n < 0 || j + n > width - 1)
                    {
                        continue;
                    }

                    blueSum[0] += image[i + m][j + n].rgbtBlue * Gx[m + 1][n + 1];
                    blueSum[1] += image[i + m][j + n].rgbtBlue * Gy[m + 1][n + 1];

                    greenSum[0] += image[i + m][j + n].rgbtGreen * Gx[m + 1][n + 1];
                    greenSum[1] += image[i + m][j + n].rgbtGreen * Gy[m + 1][n + 1];

                    redSum[0] += image[i + m][j + n].rgbtRed * Gx[m + 1][n + 1];
                    redSum[1] += image[i + m][j + n].rgbtRed * Gy[m + 1][n + 1];
                }
            }
            int b = round(sqrt(pow(blueSum[0], 2) + pow(blueSum[1], 2)));
            int g = round(sqrt(pow(greenSum[0], 2) + pow(greenSum[1], 2)));
            int r = round(sqrt(pow(redSum[0], 2) + pow(redSum[1], 2)));

            // Cap at 255
            if (b > 255)
            {
                b = 255;
            }

            if (g > 255)
            {
                g = 255;
            }

            if (r > 255)
            {
                r = 255;
            }

            tmp[i][j].rgbtBlue = b;
            tmp[i][j].rgbtGreen = g;
            tmp[i][j].rgbtRed = r;
        }
    }

    // Copy array to original array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
