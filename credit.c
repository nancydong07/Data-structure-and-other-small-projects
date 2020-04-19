#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    long cardNumber = get_long("Enter credit card number: ");
    bool numberExist = true;
    long part1 = cardNumber;
    long part3 = cardNumber;
    long times2 = 0;
    long sum = 0;
    int count = 0;
    while ((part3 / 10) != 0)
    {
        count++;
        part3 = part3 / 10;
    }
    count++;
    while (numberExist)
    {
         
        part1 = part1 / 10;
        times2 = (part1 % 10) * 2;
        part1 = part1 / 10;
        while (times2 != 0)
        {
            sum += (times2 % 10);
            times2 = times2 / 10;
        }
        if (part1 == 0)
        {
            numberExist = false;            
        }
       
        
    }
    bool numberExist2 = true;
    long part2 = cardNumber;
    long sum2 = sum;
    while (numberExist2)
    {
        sum2 += part2 % 10;
        part2 = part2 / 100;        
        if (part2 == 0)
        {
            numberExist2 = false;
        }
       
    }
    int firstDigit = cardNumber / pow(10, count - 1);
    bool visa = firstDigit == 4;
    int secondDigit = cardNumber / pow(10, count - 2);
    bool amex = (firstDigit == 3 && (secondDigit % 10 == 4 || secondDigit % 10 == 7));
    bool master = (firstDigit == 5 && (secondDigit % 10 >= 1 && secondDigit % 10 <= 5));

    if (sum2 % 10 != 0 || count < 13)
    {
        printf("INVALID\n");
    }
    else
    { 
        if (visa)
        {
            printf("VISA\n");
        }
    else if (amex)
    {
            printf("AMEX\n");
    }
    else if (master)
    {
            printf("MASTERCARD\n");
    }
   else 
   {
       printf("INVALID\n");
   }

    }
   
}

