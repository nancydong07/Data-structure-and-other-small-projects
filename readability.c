#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main (int arvc, string args[])
{
    int wordCount = 1;
    int letterCount = 0;
    int sentenceCount = 0;
    string sentence = get_string("Text: ");
    long length = strlen(sentence);
    for (int i=0; i<length; i++)
    {
        if (isalpha(sentence[i]))
        {
            letterCount++;
        }
        if (isspace(sentence[i]))
        {
            wordCount++;
        }
        if (sentence[i] == '!' || sentence[i] == '.' || sentence[i] == '?') 
        {
            sentenceCount++;    
           // wordCount++;
        }
        
        
    }
    
    float L = (float)(letterCount * 100) / wordCount;
    float S = (float)(sentenceCount * 100) / wordCount;
    int index =  round(0.0588 * L - 0.296 * S - 15.8);
    if (index > 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else if (index<1) 
    {
        printf("Before Grade 1\n");    
    }
    else
    {
        printf("Grade 16+\n");
    }
    
    
}
