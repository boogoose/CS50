#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramid(int);

int main(void) 
{
    // Get height
    int height = get_height();    
    // Print Pyramid
    print_pyramid(height);
}

int get_height(void)
{
    int height;
    do
    {
        height = get_int("How high? ");
    }
    while ((height < 1) || (height > 8));
    return height;
}

void print_pyramid(int height)
{
    for (int i = 0; i < height; i++)
    {
        // Print leading whitespace
        for (int j = 0; j < (height - i); j++)
        {
            printf(" ");
        }
        // Print both left and right blocks
        for (int k = 0; k < 2; k++)
        {
            for (int l = 0; l < (i + 1); l++)
            {
                printf("#");  
            }
            // Print central whitespace
            if (k == 0)
            {
                printf(" "); 
            }
        }
        printf("\n");
    }
}
