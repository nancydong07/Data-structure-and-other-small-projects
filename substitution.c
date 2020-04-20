#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(int argc, string args[])
{
    if (argc != 2)
    {
        printf("Enter key only\n");
        return 1;
    }
    long length = strlen(args[1]);
    if (length != 26)
    {
        printf("26 keys only\n");
        return 1;
    }
    for (int i=0; i<length; i++)
    {
        for (int j=i; j<length-1; j++)
        {
            if (args[1][i] == args[1][j+1])
            {
                printf("Duplicates \n");
                return 1; 
            }
        }
        if (isalpha(args[1][i]) == false)
        {
            printf("Alphas only \n");
            return 1; 
        }
    }
    string plain = get_string("plaintext: ");
    string cript = plain;
    int index=0;
    for (int i = 0; i < strlen(plain); i++)
    {
     
       if ((isalpha(plain[i])) && (isupper(plain[i]))) 
       {
            index = plain[i] - 65;
            cript[i] = args[1][index];
       }
       else if ((isalpha(plain[i])) && (islower(plain[i])))
       {
            index = plain[i] - 97;
            cript[i] = args[1][index];   
       }
       else
       {
           
           cript[i] = plain[i];
       }
    }
    printf("ciphertext: %s\n", cript);
}