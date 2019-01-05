// Implements a spell-checker

#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>

#include <stdbool.h>
#include <stdlib.h>
#include "dictionary.h"

// Undefine any definitions
//#undef calculate
//#undef getrusage

// Default dictionary
//#define DICTIONARY "dictionaries/large"

typedef struct node
{
    struct node* arr[27];
    bool is_word;
}
node;
node* root;
int wordCount = 0;

void freeTrie (node* root);

// Loads dictionary into memory, returning true if successful else false
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }
    char *dictionary = argv[1];

    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
    root = calloc(1, sizeof(node));

    for (char c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        int index = 0;
        node* next = root;

        for (; c != '\n'; c = fgetc(dict))
        {
            if (isalpha(c))
            {
                index = tolower(c) - 'a';
            }
            else if ((int)c == 39)
            {
                index = 26;
            }

            if (next->arr[index] == NULL)
            {
                next->arr[index] = (node *)calloc(1, sizeof(node));
            }
            next = next->arr[index];
         }

        next->is_word = true;
        ++wordCount;
    }
    freeTrie(root);
    fclose(dict);
    return true;
}

void freeTrie (node* prt)
{
    //iterate over the children
    for(int i = 0; i < 27; i++)
    {
        //if found a node inside a child
        if(prt->arr[i] != NULL)
        {
            //call recursively
            freeTrie(prt->arr[i]);
        }
    }
    //free the argument pointer
    free(prt);
    return;
}



