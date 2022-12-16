#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int conform(int q);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over rows & columns
    for (int row = 0; row < height; row++)
        {
            for (int column = 0; column < width; column++)
                {
                    // Calculate (rounded) average RGB value
                    int average = round((image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed) / 3.0);

                    // Set each RGB value to the average
                    image[row][column].rgbtBlue = average;
                    image[row][column].rgbtGreen = average;
                    image[row][column].rgbtRed = average;
                }
        }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare buffer image
    // Using malloc for the lols
    // See: https://www.geegcsforgeegcs.org/dynamically-allocate-2d-array-c/
    RGBTRIPLE (*image_buffer)[height][width] = malloc(sizeof *image_buffer);
    if (image_buffer == NULL)
    {
        printf("malloc returns NULL in allocation for image_buffer.");
        exit(1);    // using <exit() as <return> cannot return a value in void function
    }

    // Create reflected image in buffer
    for (int row = 0; row < height; row++)
        {
            // iterate over image & image_buffer columns in forward & reverse directions respectively
            int buffer_column = width - 1;
            for (int column = 0; column < width; column++)
                {
                    (*image_buffer)[row][buffer_column] = image[row][column];
                    buffer_column--;
                }
        }

    // Copy buffer to image
    for (int row = 0; row < height; row++)
        {
            for (int column = 0; column < width; column++)
                {
                    image[row][column] = (*image_buffer)[row][column];
                }
        }

    free(image_buffer);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare buffer image
    RGBTRIPLE(*image_buffer)[height][width] = malloc(sizeof *image_buffer);
    if (image_buffer == NULL)
    {
        printf("malloc returns NULL in allocation for image_buffer.");
        exit(1);    // using <exit() as <return> cannot return a value in void function
    }
    
    //  Generate blurred image in buffer
    // Loop over image rows & columns

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // initialise variables
            int red_total = 0;
            int green_total = 0;
            int blue_total = 0;

            float denominator = 0;

            // loop over 3 * 3 grid centred on pixel                    
            for (int gr = - 1; gr < 2; gr ++)   
            {
                for (int gc = -1; gc < 2; gc++)
                {
                    // Check if grid co-ordinate is in-bounds
                    if ((row + gr >= 0) &&
                        (row + gr < height) &&
                        (column + gc >= 0) &&
                        (column + gc < width))
                    {
                        // Increment running totals
                        red_total += image[row + gr][column + gc].rgbtRed;
                        green_total += image[row + gr][column + gc].rgbtGreen;
                        blue_total += image[row + gr][column + gc].rgbtBlue;

                        denominator++;
                    }
                }
            }
            // Set blurred pixel in image_buffer
            (*image_buffer)[row][column].rgbtRed = round(red_total /denominator);
            (*image_buffer)[row][column].rgbtGreen = round(green_total / denominator);
            (*image_buffer)[row][column].rgbtBlue = round(blue_total / denominator);
        }
    }
    // Copy blurred image_buffer image bacgc to original array
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column] = (*image_buffer)[row][column];
        }
    }
    free(image_buffer);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare buffer image with 1 pixel wide 'padding' around 
    RGBTRIPLE(*image_buffer)[height + 2][width + 2] = malloc(sizeof * image_buffer);
    if (image_buffer == NULL)
    {
        printf("malloc returns NULL in allocation for image_buffer.");
        exit(1);    // using <exit() as <return> cannot return a value in void function
    }

    // Create Gx & Gy arrays
    // initialising dynamically allocated array was too cumbersome!
    int Gx [3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy [3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Initialise buffer pixels to 0
    RGBTRIPLE blangc = {.rgbtBlue = 0, .rgbtGreen = 0, .rgbtRed = 0};
    for (int row = 0; row < height + 2; row++)
    {
        for (int column = 0; column < width + 2; column ++)
        {
            (*image_buffer)[row][column] = blangc;
        }
    }

    // Copy image to buffer
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            (*image_buffer)[row + 1][column + 1] = image[row][column];
        }
    }

    // Loop over actual image within buffer
    // for (int row = 1; row < height + 1; row++)
    for (int row = 0; row < height; row++)

    {
        // for (int column = 1; column < width + 1; column++)
        for (int column = 0; column < width; column++)

        {
            // Declare red, green, and blue Gx & Gy counters
            float Red_Gx = 0;
            float Green_Gx = 0;
            float Blue_Gx = 0;

            float Red_Gy = 0;
            float Green_Gy = 0;
            float Blue_Gy = 0;

            // Loop over sobel-grid
            for (int gr = 0; gr < 3; gr ++) 
            {
                for (int gc = 0; gc < 3; gc++)
                {
                    // Increment RGB_Gx/Gy counts
                    Red_Gx += ((*image_buffer)[row +gr][column+ gc].rgbtRed) * (Gx[gr][gc]);
                    Green_Gx += ((*image_buffer)[row +gr][column+ gc].rgbtGreen) * (Gx[gr][gc]);
                    Blue_Gx += ((*image_buffer)[row +gr][column+ gc].rgbtBlue) * (Gx[gr][gc]);
                    Red_Gy += ((*image_buffer)[row +gr][column+ gc].rgbtRed) * (Gy[gr][gc]);
                    Green_Gy += ((*image_buffer)[row +gr][column+ gc].rgbtGreen) * (Gy[gr][gc]);
                    Blue_Gy += ((*image_buffer)[row +gr][column+ gc].rgbtBlue) * (Gy[gr][gc]);

                    // Calculate final rgb values
                    int red_value = conform(round(sqrt(pow(Red_Gx, 2) + pow(Red_Gy, 2))));
                    int green_value = conform(round(sqrt(pow(Green_Gx, 2) + pow(Green_Gy, 2))));
                    int blue_value = conform(round(sqrt(pow(Blue_Gx, 2) + pow(Blue_Gy, 2))));

                    // Write values
                    image[row][column].rgbtRed = red_value;
                    image[row][column].rgbtGreen = green_value;
                    image[row][column].rgbtBlue = blue_value;
                }
            }

        }
    }
}

// Conform function
int conform(int q)
{
    if (q > 255)
    {
        q = 255;
    }
    return q;
}
