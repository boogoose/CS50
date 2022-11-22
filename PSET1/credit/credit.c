#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    long number = get_long("Number: ");  
    int length = 0;
    int digit = 0;
    int following_digit = 0;
    int doubled_digit = digit * 2;
    int sum = 0;
    int checksum = (sum % 10);

    while (number > 0)
    {
        length ++;
        if ((length % 2 == 0))  // every 2nd digit (in reverse)
        {
            following_digit = digit;
            digit = number % 10;

            for (int i = 0; i < 2; i++) // loops over both 'numerals' and 'tens' columns
            {
                sum = sum + (doubled_digit % 10);
                doubled_digit = doubled_digit / 10;
            }
        }
        else // every odd numbered digit (in reverse)
        {
            following_digit = digit;
            digit = number % 10;
            sum = sum + digit;
        }
        number = (number / 10); // integer division effects removal of last digit
    }

  if ((checksum == 0) &&
    (length == 15) &&
    (digit == 3) && (following_digit == 4 || following_digit == 7))
  {
    printf ("AMEX\n");
  }

  else if ((checksum == 0) &&
    (length == 16) && (digit == 5) &&
    (following_digit > 0) && (following_digit < 6))
  {
    printf ("MASTERCARD\n");
  }

  else if ((checksum == 0) &&
    (length == 13 || length == 16) &&
    (digit == 4))
  {
    printf ("VISA\n");
  }

  else
    printf ("INVALID\n");

  // test comment
}







