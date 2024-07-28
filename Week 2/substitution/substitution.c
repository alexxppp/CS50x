#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

string cipher(string key, string text);

string alphabet = "abcdefghijklmnopqrstuvwxyz";
string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main(int argc, string argv[])
{
    if (argc != 2 || strlen(argv[1]) != 26)
    {
        printf("Usage: ./cipher key\n");
        return 1;
    }

    for (int i = 0, length = strlen(argv[1]); i < length; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters\n");
            return 1;
        }

        for (int j = i + 1; j < length; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must not contain repeated characters\n");
                return 1;
            }
        }
    }

    string key = argv[1];
    string text = get_string("plaintext: ");
    printf("ciphertext: %s\n", cipher(key, text));
    return 0;
}

string cipher(string key, string text)
{
    int lengthText = strlen(text);
    string output = malloc(lengthText + 1);

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        if (isalpha(text[i]))
        {
            char c = text[i];
            int index = toupper(c) - 'A';
            if (islower(c))
            {
                output[i] = tolower(key[index]);
            }
            else
            {
                output[i] = toupper(key[index]);
            }
        }
        else
        {
            output[i] = text[i];
        }
    }
    output[lengthText] = '\0';
    return output;
}
