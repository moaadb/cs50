#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            average = round(average);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
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
            int tmpBlue = image[i][j].rgbtBlue;
            int tmpGreen = image[i][j].rgbtGreen;
            int tmpRed = image[i][j].rgbtRed;

            // reflect vertically
            // image[i][j].rgbtBlue = image[height - i - 1][j].rgbtBlue;
            // image[i][j].rgbtGreen = image[height - i - 1][j].rgbtGreen;
            // image[i][j].rgbtRed = image[height - i - 1][j].rgbtRed;

            // image[height - i - 1][j].rgbtBlue = tmpBlue;
            // image[height - i - 1][j].rgbtGreen = tmpGreen;
            // image[height - i - 1][j].rgbtRed = tmpRed;

            // reflect horizontally
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = tmpBlue;
            image[i][width - j - 1].rgbtGreen = tmpGreen;
            image[i][width - j - 1].rgbtRed = tmpRed;
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
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avgBlue = 0.0;
            float avgGreen = 0.0;
            float avgRed = 0.0;

            // top left corner
            if (i == 0 && j == 0)
            {
                avgBlue =
                    (copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0;
                avgGreen =
                    (copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                    4.0;
                avgRed = (copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0;
            }
            // top right corner
            else if (i == 0 && j == width - 1)
            {
                avgBlue =
                    (copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / 4.0;
                avgGreen =
                    (copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                    4.0;
                avgRed = (copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) / 4.0;
            }
            // bottom left corner
            else if (i == height - 1 && j == 0)
            {
                avgBlue =
                    (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0;
                avgGreen =
                    (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                    4.0;
                avgRed = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0;
            }
            // bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                avgBlue =
                    (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / 4.0;
                avgGreen =
                    (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                    4.0;
                avgRed = (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) / 4.0;
            }
            // top edge
            else if (i == 0 && j != 0)
            {
                avgBlue = (copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                           copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) /
                          6.0;
                avgGreen = (copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                            copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) /
                           6.0;
                avgRed = (copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                          copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                         6.0;
            }
            // bottom edge
            else if (i == height - 1 && j != 0)
            {
                avgBlue = (copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                           copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) /
                          6.0;
                avgGreen = (copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                            copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) /
                           6.0;
                avgRed = (copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                          copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                         6.0;
            }
            // left edge
            else if (i != 0 && j == 0)
            {
                avgBlue = (copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i][j].rgbtBlue) /
                          6.0;
                avgGreen = (copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                            copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i][j].rgbtGreen) /
                           6.0;
                avgRed = (copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j].rgbtRed +
                          copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i][j].rgbtRed) /
                         6.0;
            }
            // right edge
            else if (i != 0 && j == width - 1)
            {
                avgBlue = (copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) /
                          6.0;
                avgGreen = (copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                            copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) /
                           6.0;
                avgRed = (copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                          copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                         6.0;
            }
            else
            {
                // not a corner or edge
                avgBlue = (copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                           copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue +
                           copy[i][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) /
                          9.0;
                avgGreen = (copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                            copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen +
                            copy[i][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) /
                           9.0;
                avgRed = (copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                          copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed +
                          copy[i][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                         9.0;
            }

            avgBlue = round(avgBlue);
            avgGreen = round(avgGreen);
            avgRed = round(avgRed);

            // resulting blurred pixel's color values
            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;
        }
    }

    return;
}
