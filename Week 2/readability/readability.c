#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int countStuffAndReturn(string text);

int main(void) // space equals 32. dot equals 46     //hello world. i think today is gonna be a good
               // day has 38 letters in it.
{
    string text = get_string("Give me a text: ");
    if (countStuffAndReturn(text) > 16)
    {
        printf("Grade 16+\n");
    }
    else if (countStuffAndReturn(text) < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", countStuffAndReturn(text));
    }
}

int countStuffAndReturn(string text)
{
    int letters = 0, words = 0, sentences = 0;
    int value;
    for (int i = 0, length = strlen(text); i < length + 1; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letters++;
        }
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences++;
        }
        else if (text[i] == ' ' || text[i] == '\0')
        {
            words++;
        }
    }

    float avgWordsEvery100 = (100 / (float) words) * (float) letters;
    float avgSentencesEvery100 = (100 / (float) words) * (float) sentences;
    value = round(0.0588 * avgWordsEvery100 - 0.296 * avgSentencesEvery100 - 15.8);

    return value;
}
