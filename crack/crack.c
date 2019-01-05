#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, string argv[])
{
    // define a array to store salt
    char salt[3];
    salt[2] = '\0';
    // test array to store passwords of all lengths
    char test[5] = {};
    test[4] = '\0';
    // generate_test to store all 4 letter possible passwords
    char generate_test[5] = {};
    //check if there are two command-line arguments,
    //if not, print out error message and return 1
    if (argc != 2)
    {
        printf("Usage: %s hash\n", argv[0]);
        return 1;
    }
    else
    {
        // get salt from input hash
        for (int i = 0; i < 2; i ++)
        {
            salt[i] = argv[1][i];
        }
        // store all ASCII characters in an array
        char arr[52];
        for (int j = 65; j < 91; j++)
        {
            arr[j - 65] = (char)(j);
        }
        for (int k = 97; k < 123; k++)
        {
            arr[k - 71] = (char)(k);
        }
        // get all 4 letter possible passwords
        for (int l = 0; l < 52; l ++)
            for (int m = 0; m < 52; m ++)
                for (int n = 0; n < 52; n ++)
                    for (int p = 0; p < 52; p ++)
                    {
                        generate_test[0] = arr[l];
                        generate_test[1] = arr[m];
                        generate_test[2] = arr[n];
                        generate_test[3] = arr[p];
                        // for each of the 4 letter possible password, break down to shorter possible passwords to test
                        for (int r = 4; r > 0; r --)
                        {
                            // take r characters
                            strncpy(test, generate_test, r);
                            test[r] = '\0';
                            // try password of length r
                            if (strcmp(crypt(test, salt), argv[1]) == 0)
                            {
                                printf("Password found!\n%s\n", test);
                                return 0;
                            }

                        }
                    }

    }
}