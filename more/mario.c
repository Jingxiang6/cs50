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
        //print space on the left side
        for (int k = 0; k < i - 1 - j; k++)
        {
            printf(" ");
        }
        //print # on the left side
        for (int h = 0; h < j + 1; h++)
        {
            printf("#");
        }
        //print two spaces in the middle
        printf("  ");
        //print # on the right side
        for (int h = 0; h < j + 1; h++)
        {
            printf("#");
        }
        //print space on the right side
        for (int k = 0; k < i - 1 - j; k++)
        {
            printf(" ");
        }
        //print next line
        printf("\n");
    }
}