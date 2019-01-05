# import sys and crypt
from crypt import crypt
import sys


def main():
    # check if there are two command-line arguments,
    # if not, print out error message and return 1
    if (len(sys.argv) != 2):
        print("Usage: crack.py hash")
        exit(1)
    # if there are two command-line arguments input
    else:
        # define generate_test as an array to store possible password
        generate_test = []
        # get salt from the first two characters of sys.argv[1]
        salt = sys.argv[1][:2]
        # store all the alpharbetical in an array
        arr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
        for i in range(52):
            for j in range(52):
                for k in range(52):
                    for m in range(52):
                        # all the possible one, two, three, and four letters passwords
                        generate_test = [arr[i], arr[i] + arr[j], arr[i] + arr[j] + arr[k], arr[i] + arr[j] + arr[k] + arr[m]]
                        # hash password from each elem
                        for elem in generate_test:
                            # if hashed password is the same as sys.argv[1], print elem
                            if crypt(elem, salt) == sys.argv[1]:
                                print("Password found!")
                                print(elem)
                                exit(0)


if __name__ == "__main__":
    main()