#include <cs50.h>
#include <stdio.h>
#include <string.h>

string compareValue(int value1, int value2);
int checkValue(string word);

string alphabet = "abcdefghijklmnopqrstuvwxyz";
string capAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int score[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string input1 = get_string("Number 1: ");
    string input2 = get_string("Number 2: ");
    printf("%s\n", compareValue(checkValue(input1), checkValue(input2)));
}

int checkValue(string word)
{
    int value = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        for (int j = 0; j < strlen(alphabet); j++)
        {
            if (word[i] == alphabet[j] || word[i] == capAlphabet[j])
            {
                value += score[j];
            }
        }
    }
    return value;
}

string compareValue(int value1, int value2)
{
    if (value1 < value2)
    {
        return "Player 2 wins!";
    }
    else if (value1 > value2)
    {
        return "Player 1 wins!";
    }
    else
    {
        return "Tie!";
    }
}
