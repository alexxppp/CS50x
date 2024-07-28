// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

const int TABLE_SIZE = 65536;

node *table[TABLE_SIZE];

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value = (hash_value << 2) ^ tolower((unsigned char)word[i]);
    }
    return hash_value % TABLE_SIZE;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    for (node *trav = table[index]; trav != NULL; trav = trav->next)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char buffer[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            fclose(file);
            return false;
        }

        strcpy(new_node->word, buffer);
        unsigned int index = hash(new_node->word);
        new_node->next = table[index];
        table[index] = new_node;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int total_words = 0;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        for (node *trav = table[i]; trav != NULL; trav = trav->next)
        {
            total_words++;
        }
    }
    return total_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        node *trav = table[i];
        while (trav != NULL)
        {
            node *temp = trav;
            trav = trav->next;
            free(temp);
        }
    }
    return true;
}
