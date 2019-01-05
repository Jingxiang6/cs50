# import sys and get_string
import sys
from cs50 import get_string


def main():
    # check if there are two command-line arguments,
    # if not, print out error message and return 1
    if (len(sys.argv) != 2):
        print("Usage: vigenere.py keyword")
        exit(1)

    else:  # if there are two command-line arguments, executive following...
        for c in sys.argv[1]:
            if not c.isalpha():  # print error message if contains any non-alphabetical character
                print("Usage: vigenere.py keyword")
                exit(1)

    # prompt the user for a plaintext
    p_text = get_string("plaintext: ")
    # number of non alphabetic characters in plaintext, count_nonalpha
    count_nonalpha = 0
    n = len(p_text)  # get p_text length in n
    m = len(sys.argv[1])
    print("ciphertext: ", end="")
    # decipher plaintext char by char
    for i in range(n):
        if p_text[i].isalpha():  # if char is alphabetic letter, decipher
            j = (i - count_nonalpha) % m  # get the index in argv[1] to decipher p_text[i]
            if (p_text[i].isupper()):  # if char is uppercase
                if (((ord(p_text[i]) - 64 + ord(sys.argv[1][j].upper()) - 65) % 26) == 0):  # when it reach Z
                    c = 'Z'
                else:
                    c = chr((ord(p_text[i]) - 64 + ord(sys.argv[1][j].upper()) - 65) % 26 + 64)  # when it's between A and Z
            elif (p_text[i].islower()):  # if char is lowercase
                if (((ord(p_text[i]) - 96 + ord(sys.argv[1][j].upper()) - 65) % 26) == 0):  # when it reach z
                    c = 'z'
                else:
                    c = chr((ord(p_text[i]) - 96 + ord(sys.argv[1][j].upper()) - 65) % 26 + 96)  # when it's between a and z
        else:  # if char is not an alphabetic
            count_nonalpha += 1  # count the non alpha characters in plaintext
            c = p_text[i]  # if char is not alphabetic letter, leave it unchanged
        print(c, end="")  # print out ciphertext
    # print a new line
    print()


if __name__ == "__main__":
    main()