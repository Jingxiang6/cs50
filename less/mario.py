# import get_int function from cs50
from cs50 import get_int

# prompt the user to input the height [0,23]
while True:
    height = get_int("height: ")
    if (height >= 0) and (height < 24):
        break
# print the spaces and #s
for i in range(height):
    print(" " * (height - 1 - i), end="")
    print("#" * (i + 2))