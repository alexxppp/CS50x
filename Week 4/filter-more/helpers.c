#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int averageColor =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = averageColor;
            image[i][j].rgbtGreen = averageColor;
            image[i][j].rgbtRed = averageColor;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tempPixel = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tempPixel;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBlue = 0, sumGreen = 0, sumRed = 0;
            int count = 0;

            // Sum the values of the neighboring pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumBlue += image[ni][nj].rgbtBlue;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumRed += image[ni][nj].rgbtRed;
                        count++;
                    }
                }
            }

            copy[i][j].rgbtBlue = round((float) sumBlue / count);
            copy[i][j].rgbtGreen = round((float) sumGreen / count);
            copy[i][j].rgbtRed = round((float) sumRed / count);
        }
    }

    // Copy the blurred values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edgeImage[height][width];

    // Sobel kernels
    int GxKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int GyKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxBlue = 0, GyBlue = 0;
            int GxGreen = 0, GyGreen = 0;
            int GxRed = 0, GyRed = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        int kernelValueX = GxKernel[di + 1][dj + 1];
                        int kernelValueY = GyKernel[di + 1][dj + 1];

                        GxBlue += image[ni][nj].rgbtBlue * kernelValueX;
                        GyBlue += image[ni][nj].rgbtBlue * kernelValueY;

                        GxGreen += image[ni][nj].rgbtGreen * kernelValueX;
                        GyGreen += image[ni][nj].rgbtGreen * kernelValueY;

                        GxRed += image[ni][nj].rgbtRed * kernelValueX;
                        GyRed += image[ni][nj].rgbtRed * kernelValueY;
                    }
                }
            }

            int newBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            int newGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            int newRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));

            edgeImage[i][j].rgbtBlue = (newBlue > 255) ? 255 : newBlue;
            edgeImage[i][j].rgbtGreen = (newGreen > 255) ? 255 : newGreen;
            edgeImage[i][j].rgbtRed = (newRed > 255) ? 255 : newRed;
        }
    }

    // Copy the edge-detected values back to the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edgeImage[i][j];
        }
    }
}
