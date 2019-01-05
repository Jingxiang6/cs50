#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check if there are two command-line arguments,
    //if not, print out error message and return 1
    if (argc != 2)
    {
        printf("Usage: %s k\n", argv[0]);
        return 1;
    }
    else // if there are two command-line arguments, executive following...
    {
        int m = strlen(argv[1]);
        for (int i = 0; i < m; i ++)
        {
            if (!(isalpha(argv[1][i]))) //print error message if contains any non-alphabetical character
            {
                printf("Usage: %s k\n", argv[0]);
                return 1;
            }
            else
            {
                if (islower(argv[1][i]))
                {
                    argv[1][i] = toupper(argv[1][i]);
                }
            }
        }
//        printf("%s\n",argv[1]);
        //prompt the user for a plaintext
        string p_text = get_string("plaintext: ");
        //number of non alphabetic characters in plaintext, count_nonalpha
        int count_nonalpha = 0, n = strlen(p_text); //get p_text length in n
        char c_text[n + 1]; //ciphertext string
        c_text[n] = '\0';
        //decipher plaintext char by char
        for (int i = 0; i < n; i ++)
        {
            if (isalpha(p_text[i]))  //if char is alphabetic letter, decipher
            {
                int j = (i - count_nonalpha) % m; //get the index in argv[1] to decipher p_text[i]
                if (isupper(p_text[i])) //if char is uppercase
                {
                    if (((p_text[i] - 64 + argv[1][j] - 65) % 26) == 0) //when it reach Z
                    {
                        c_text[i] = 'Z';
                    }
                    else
                    {
                        c_text[i] = (p_text[i] - 64 + argv[1][j] - 65) % 26 + 64; //when it's between A and Z
                    }
                }
                else if (islower(p_text[i])) //if char is lowercase
                {
                    if (((p_text[i] - 96 + argv[1][j] - 65) % 26) == 0) //when it reach z
                    {
                        c_text[i] = 'z';
                    }
                    else
                    {
                        c_text[i] = (p_text[i] - 96 + argv[1][j] - 65) % 26 + 96; //when it's between a and z
                    }
                }
            }
            else if (!(isalpha(p_text[i])))
            {
                count_nonalpha += 1; //count the non alpha characters in plaintext
                c_text[i] = p_text[i]; //if char is not alphabetic letter, leave it unchanged
            }
        }
        printf("ciphertext: %s\n", c_text); //print out ciphertext
    }
    return 0;
}