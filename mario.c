#include <cs50.h>
#include <stdio.h>

int main(void)
{
      int Height=0;
   do 
    {
    Height= get_int("Height: ");
    }
    while (Height>8 || Height<1);
    for (int i=1; i<=Height; i++){
        for (int j=1; j<=Height-i; j++){
            
            printf(" ");
        }
        for (int k=1; k<=i; k++){
            printf("#");
        }
        printf("  ");
        for (int h=1; h<=i; h++){
            printf("#");
        }
        printf("\n");
    }
}
