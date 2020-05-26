// Implements a dictionary's functionality

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"
#include <math.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 11001;
int count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char word2[LENGTH +1];
    int i = 0; 
    for (; word[i] != '\0'; i++)
    {
         word2[i] = (tolower(word[i]));
    }
    word2[i] = '\0';
    int index = hash(word2);
  //  printf("index of word is %i and test word is %s\n", index, word2);


//    printf("leng is %lu \n", strlen(word2));
    node *head = table[index];

    for (node *cursor = head; cursor != NULL; cursor = cursor->next)
    {

        if (strcasecmp(word2, cursor->word) == 0)
        {
            return true;
        }
    }
    

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int num = 0;
    for (int i = 0; word[i]/4 != '\0'; i++)
    {
        num += (word[i] + sqrt(word[strlen(word) - i - 1])) * (strlen(word));
    }
    num = num % N;
    return num;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO'
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    node *n;
    int index = 0;
    while (fscanf(file, "%s", buffer) != EOF) //read string from the file and putting it into the word array
    {
        n = malloc(sizeof(node));
        strcpy(n->word, buffer); // copy the word to the node n's word field
        index = hash(n->word);

        n->next = NULL;
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
            count++;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
            count++;
        }

    }
 /* for (int j = 0; j < N; j++)
    {
        for (node *cursor = table[j]; cursor!=NULL; cursor = cursor->next)
        {
            printf("[%i] --> %s", j, cursor->word);
        }
        printf("\n");
    }  */  fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *cursor = NULL;
    node *temp = cursor;

    for(int i = 0; i < N; i++)
    {
        for (cursor = table[i]; cursor != NULL; )
        {
            temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}
