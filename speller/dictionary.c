// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

//define trie node structure
typedef struct node
{
    struct node* arr[27];
    bool is_word;
}
node;

// define root pointer
node* root;

// initialize wordCount to count the number of words load from dictionary to trie
int wordCount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //Get words length
    int wordLength = strlen(word);

    // define and initialize pointer next = root
    node* next = root;

    // check the word character by character
    for(int i = 0; i < wordLength; i++)
    {
        // initialize the index of array in trie
        int index = 0;

        // to check is character in the word is alphabetical or '
        if (isalpha(word[i]))
        {
            index = tolower(word[i]) - 'a';
        }
        else if ((int)word[i] == 39)
        {
            index = (26);
        }

        // if pointer to character is NULL, the word doesn't exist
        if (next->arr[index] == NULL)
        {
            return false;
        }
        // move to the next pointer if a pointer to previous character exist
        next = next->arr[index];
    }
    //Return what is_word return
    return next->is_word;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //open the dictinary, and print error if it doesn't exist
    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }
    // initialize pointer root in dynamically allocate memory
    root = calloc(1, sizeof(node));

    // load each word character by character before reaching EOF
    for (char c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // initialize the index of array
        int index = 0;

        // initialize pointer next = root
        node* next = root;

        // for one word, load character c when it's alphabetical or '
        for (; c != '\n' && c != EOF; c = fgetc(dict))
        {
            if (isalpha(c))
            {
                index = c - 'a';
            }
            else if ((int)c == 39)
            {
                index = (26);
            }

            // if the pointer to c doesn't exist, create a new pointer
            if (next->arr[index] == NULL)
            {
                next->arr[index] = (node *)calloc(1, sizeof(node));
            }
            // move to the next pointer
            next = next->arr[index];
        }

        // is_word is true after loading the last character
        next->is_word = true;
        // count the number of loaded words
        wordCount ++;
    }
    // close dictionary after loading
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // return the word counter wordCount
    return wordCount;
}

// recursive function to free dynamically allocate memory
bool freeTrie (node* prt)
{
    //iterate over the array size
    for(int i = 0; i < 27; i++)
    {
        //if found a node inside an array
        if(prt->arr[i] != NULL)
        {
            //call recursively
            freeTrie(prt->arr[i]);
        }
    }
    //free the argument pointer
    free(prt);
    return true;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // run the freeTrie function and return boolean value
    return freeTrie(root);
}
