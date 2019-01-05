#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check if there are two command-line argument,
    //if not, print out error message and return 1
    if (argc != 2)
    {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }
    //if there are two command-line argument, executive following...
    else
    {
        //prompt the user for a plaintext
        string p_text = get_string("plaintext: ");
        //convert the key from string to int, and get p_text length in n
        int k = atoi(argv[1]), n = strlen(p_text);
        char c_text[n + 1]; //ciphertext string
        c_text[n] = '\0';
        //decipher plaintext char by char
        for (int i = 0; i < n; i ++)
        {
            if (isalpha(p_text[i]))  //if char is alphabetic letter, decipher
            {
                if (isupper(p_text[i])) //if char is uppercase
                {
                    if (((p_text[i] - 64 + k) % 26) == 0) //when it reach Z
                    {
                        c_text[i] = 'Z';
                    }
                    else
                    {
                        c_text[i] = (p_text[i] - 64 + k) % 26 + 64; //when it's between A and Z
                    }
                }
                else if (islower(p_text[i])) //if char is lowercase
                {
                    if (((p_text[i] - 96 + k) % 26) == 0) //when it reach z
                    {
                        c_text[i] = 'z';
                    }
                    else
                    {
                        c_text[i] = (p_text[i] - 96 + k) % 26 + 96; //when it's between a and z
                    }
                }
            }
            else
            {
                c_text[i] = p_text[i]; //if char is not alphabetic letter, leave it unchanged
            }
        }
        printf("ciphertext: %s\n", c_text); //print out ciphertext

    }
    return 0;
}