#include <cs50.h>
#include <stdio.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void) 
{
    //Get input
    string text = get_string("Text: ");
    count_letters(text);
    count_words(text);
    count_sentences(text);

    printf("Letters: %i\n", count_letters(text));
}

int count_letters(string text)
{
    // loop over each character & count it if a letter
    int sum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (((text[i] > 64) && (text[i] < 91)) || // Upper Case         
            ((text[i] > 96) && (text[i] < 123)))
        {
            sum ++;
        }
        i ++;
    }
    return sum;
}

int count_words(string text)
{
    return 1;
}

int count_sentences(string text)
{
    return 1;    
}
