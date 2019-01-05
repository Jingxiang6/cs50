#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)

{
    //type a non-nagetive credit card number, without spaces or "-"
    long number;
    do
    {
      number = get_long_long("Number: ");
    }
    while (number < 0);

//    printf("%li", number);
    int sum = 0; //definine sum = every the other digit * 2 + left every the other digit
    int two_d; //digit * 2
    long digit1 = number; //transit number
    //sum of every the other digit * 2, starting the second to last digit
    for (int i = 0; digit1 > 100; i ++)
    {
        digit1 = number / pow(10, 2 * i + 1);
        two_d = (digit1 % 10) * 2;
        if (two_d < 10)
        {
            sum += two_d;
        }
        if (two_d >= 10)
        {
            sum += two_d % 10 + two_d / 10;
        }

//        printf("%i\n", sum);
    }
    //sum of every the other digit * 2, starting the second to last digit, plus the left digit
    long digit2 = number;
    for (int i = 0; digit2 > 10; i ++)
    {
        digit2 = number / pow(10, 2 * i);
        sum += digit2 % 10;
//        printf("%i\n", sum);
    }

//    printf("%i\n", sum);
    //count the length of number n, and get the first digit and first two digit
    long digit3 = number;
    int n = 0;
    int first_d = 0;
    int first_two_d = 0;

    while(digit3 != 0)
    {
        digit3 /= 10;
        ++ n;
        if (digit3 > 10 && digit3 < 100)
        {
            first_two_d = digit3;
        }
        if (digit3 > 1 && digit3 < 10)
        {
            first_d = digit3;
        }
    }
//    printf("%i\n", n);
//    printf("%i\n %i\n", first_two_d, first_d);
    //print VISA, AMEX,MASTERCARD or INVALID
    if (sum % 10 == 0)
    {
       if (first_d == 4 && (n == 13 || n == 16))
       {
           printf("VISA\n");
       }
       if ((first_two_d == 34 || first_two_d == 37) && (n == 15))
       {
           printf("AMEX\n");
       }
       if ((first_two_d == 51 || first_two_d == 52 || first_two_d == 53 || first_two_d == 54 || first_two_d == 55) && (n == 16))
       {
           printf("MASTERCARD\n");
       }
       else
       {
           printf("INVALID\n");
       }
    }
    else
    {
        printf("INVALID\n");
    }

}