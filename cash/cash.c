#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)

{
    //type a non-nagetive value of cash owed, unit in $
    float cash;
    do
    {
      cash = get_float("Change owed: ");
    }
    while (cash < 0);

    //print out the change owed
//    printf("Change owed: %.2f\n", cash);

    //convert cash to cents
    int cents = round (cash * 100);
    int num_coins = 0;
//    printf("%i", cents);

    //count the number of quarters
    while (cents >= 25)
    {
        cents = cents - 25;
        num_coins += 1;
    }
    //count the number of dimes
    while (cents < 25 && cents >= 10)
    {
        cents = cents - 10;
        num_coins += 1;
    }
    //count the number of nickels
    while(cents < 10 && cents >= 5)
    {
        cents = cents - 5;
        num_coins += 1;
    }
    //count the number of pennies
    while(cents < 5 && cents >= 1)
    {
        cents = cents - 1;
        num_coins += 1;
    }

    //print the total number of coins
    printf("%i\n", num_coins);

}