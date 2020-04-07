#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("hello, world\n");
    string name= get_string("What is your name?\n"); //to get user input
    printf("Hello, %s\n", name); //%s is the place holder for user input

}
