// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

#define SIZE 1000

typedef struct node
{
    char word[LENGTH + 1];
    struct node * next;
}
node;

int dictionary_size = 0;

node * hashtable[SIZE];


int hash(const char * word)
{
    int hash = 0;
    int n;
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(word[i]))
        {
            n = word[i] - 'a' + 1;
        }
        else
        {
            n = 27;
        }

        hash = ((hash << 3) + n) % SIZE;
    }
    return hash;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    node * g = hashtable[hash(word)];
    while(true)
    {
        if(strcasecmp(word, g->word) == 0)
        {
            return true;
        }
        else if(g->next == NULL)
        {
            break;
        }
        g = g->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    // TODO
    FILE * file = fopen(dictionary, "r");
    if (file == NULL)
    {
        fclose(file);
        return false;
    }
    while(fscanf(file, "%s", word) != EOF)
    {
        node * new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        strcpy(new_node->word, word);
        dictionary_size++;
        new_node->next = hashtable[hash(word)];
        hashtable[hash(word)] = new_node;
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node * temp;
    node * cursor;
    for (int i = 0; i < SIZE; i++)
    {
        cursor = hashtable[i];
        while(cursor != NULL)
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}