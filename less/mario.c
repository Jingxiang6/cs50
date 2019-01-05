#include <cs50.h>
#include <stdio.h>
int main(void)

{
    //type a integer height between 1 and 23
    int i;
    do
    {
      i = get_int("height: ");
    }
    while ((i <= 0) || (i > 23));

    //print symbol from top row to bottom
    for (int j = 0; j < i; j++)
    {
        //print space in row
        for (int k = 0; k < i - 1 - j; k++)
        {
            printf(" ");
        }
        //print # in row
        for (int h = 0; h < j + 2; h++)
        {
            printf("#");
        }
        //print next line
        printf("\n");
    }
}