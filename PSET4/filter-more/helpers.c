#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    // See: https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
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
    //bool in_bounds = false;
    // Declare buffer image
    RGBTRIPLE(*image_buffer)[height][width] = malloc(sizeof * image_buffer);
    if (image_buffer == NULL)
    {
        printf("malloc returns NULL in allocation for image_buffer.");
        exit(1);    // using <exit() as <return> cannot return a value in void function
    }
    
    // Loop over image & generate blurred image in buffer
    // Loop over row & columns
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // initialise variables
            int red_total = 0;
            int green_total = 0;
            int blue_total = 0;

            float denominator = 0;

            // loop over 3 * 3 local gride                    
            for (int gr = - 1; gr < 2; gr ++)
            {
                for (int gc = -1; gc < 2; gc++)
                {
                    int ar = (row + gr);
                    int ac = column + gc;
                    // check if pixel's in-bounds

                    if ((row + gr >= 0) &&
                        (row + gr < height) &&
                        (column + gc >= 0) &&
                        (column + gc < width))
                    {
                        //in_bounds = true; 
                        printf("in-bounds\n");

                        red_total += image[row + gr][column + gc].rgbtRed;
                        green_total += image[row + gr][column + gc].rgbtGreen;
                        blue_total += image[row + gr][column + gc].rgbtBlue;
                        printf("blue total: %i\n", blue_total);

                        denominator++;
                    }

                    else
                    {
                        printf("out of bounds\n");
                    }
                }
            }
            // Set blurred buffer pixel
            (*image_buffer)[row][column].rgbtRed = round(red_total /denominator);
            (*image_buffer)[row][column].rgbtGreen = round(green_total / denominator);
            (*image_buffer)[row][column].rgbtBlue = round(blue_total / denominator);
            printf("blue: %i\n", (*image_buffer)[row][column].rgbtBlue);
        

        }
    }
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column] = (*image_buffer)[row][column];
            //image[row][column].rgbtRed = (*image_buffer)[row][column].rgbtRed;
            //image[row][column].rgbtGreen = (*image_buffer)[row][column].rgbtGreen;
            //image[row][column].rgbtBlue = (*image_buffer)[row][column].rgbtBlue;
        }
    }
    free(image_buffer);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

