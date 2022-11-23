#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    long number = get_long("Number: ");  
    int digit_counter = 0;
    int digit = 0;
    int following_digit = 0;
    int sum = 0;

    while (number > 0)
    {
        digit_counter ++;
        if ((digit_counter % 2 == 0))  // digit's *order* (in reverse) is even
        {
            following_digit = digit;
            digit = number % 10;
            int doubled_digit = digit * 2;
            while (doubled_digit > 0)    // loops over 'units' and 'tens' columns...
            {
                sum = sum + (doubled_digit % 10);
                doubled_digit = doubled_digit / 10; // integer division effects removal of last digit
            }
        }
        else // every odd numbered digit (in reverse)
        {
            following_digit = digit;
            digit = number % 10;
            sum = sum + digit;
        }
        number = (number / 10); 
    }

    int checksum = (sum % 10);

    if ((checksum == 0) &&
        (digit_counter == 15) &&
        (digit == 3) && (following_digit == 4 || following_digit == 7))
    {
        printf("AMEX\n");
    }

    else if ((checksum == 0) &&
             ((digit_counter == 16) && (digit == 5)) &&
             (following_digit > 0) && (following_digit < 6))
    {
        printf("MASTERCARD\n");
    }

    else if ((checksum == 0) &&
             (digit_counter == 13 || digit_counter == 16) &&
             (digit == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    
}
