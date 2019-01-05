# import sys and get_string
import sys
from cs50 import get_string


def main():
    # get the convert key from input
    key = int(sys.argv[1])
    # prompt the user for correct input
    if (len(sys.argv) != 2 or key < 0):
        print("Usage: python caesar.py k")
        exit(1)

    # prompt the user for a plaintext
    plaintext = get_string("plaintext: ")
    # get ready to print out the ciphertext
    print("ciphertext: ", end="")
    # convert the plaintext to ciphertext character by character
    for p in plaintext:
        # convert if p is an alphabetical
        if p.isalpha():
            # if p is lower case
            if p.islower():
                if (((ord(p) - 96 + key) % 26) == 0):  # when it reach z
                    c = 'z'
                else:
                    c = chr((ord(p) - 96 + key) % 26 + 96)  # when it's between a and z
            # if p is upper case
            elif p.isupper():
                if (((ord(p) - 64 + key) % 26) == 0):  # when it reach Z)
                    c = 'Z'
                else:
                    c = chr((ord(p) - 64 + key) % 26 + 64)  # when it's between A and Z
        # if p is not an alphabetical, keep it unchanged
        else:
            c = p
        # print ciphertext character by character
        print(c, end="")
    # print a new line
    print()


if __name__ == "__main__":
    main()
