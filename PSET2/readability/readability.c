#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void) 
{
    //Get input
    string text = get_string("Text: ");
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);

    printf("Letters: %i\n", letter_count);
    printf("Words: %i\n", word_count);
    printf("Sentences: %i\n", sentence_count);

    float L = 100 / (float)  word_count * letter_count;
    printf("Average number of letters per 100 words: %f\n", L);
    float S = 100 / (float) word_count * sentence_count;
    printf("Average number of sentences per 100 words: %f\n",S);
    float index = 0.0588 * L - 0.296 * S - 15.8;
    printf("Index: %f\n", index);

    int grade = round(index);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    // loop over each character & count it if a letter
    int sum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (((text[i] > 64) && (text[i] < 91)) ||   // Upper Case         
            ((text[i] > 96) && (text[i] < 123)))    // Lower Case
        {
            sum ++;
        }
        i ++;
    }
    return sum;
}

int count_words(string text)
{
    // loop over each character & count the spaces
    int sum =  0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (text[i] == ' ')
        {
            sum ++;
        }
        i++;
    }
    sum ++;     // number of words = one more than spaces
    return (sum);     
}

int count_sentences(string text)
{
    // Loop over each character, incrementing count if it's a '.', a '!', or a '?'
    int sum = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if ((text[i] == '.') ||
            (text[i] == '!') ||
            (text[i] == '?'))
        {
            sum ++;
        }
        i ++;
    }

    return sum;    
}
