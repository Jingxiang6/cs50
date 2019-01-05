# import get_float function from cs50
from cs50 import get_float

# prompt the user to input a credit card number
while True:
    credit = get_float("Number: ")
    if credit > 0:
        break

# convert credit card number to a string
str_credit = str(int(credit))
# get the length of the string
length = len(str_credit)

sum = 0
# calculate the sum of every the other digit times 2, from the second-last digit
for i in range(length - 2, -1, -2):
    double_digit = 2 * int(str_credit[i])
    str_double_digit = str(double_digit)
    if len(str_double_digit) == 2:
        sum += int(str_double_digit[0]) + int(str_double_digit[1])
    else:
        sum += double_digit
# sum the other digit together
for j in range(length - 1, -1, -2):
    sum += int(str_credit[j])

# if the sum is dividable by 10
if (sum % 10 == 0):
    # VISA
    if (length == 13 or length == 16) and (str_credit[0] == '4'):
        print("VISA")
    # AMEX
    elif (length == 15) and ((str_credit[0] == '3') and (str_credit[1] == '4' or str_credit[1] == '7')):
        print("AMEX")
    # MASTERCARD
    elif (length == 16) and (str_credit[0] == '5' and (str_credit[1] == '1' or str_credit[1] == '2' or
                                                       str_credit[1] == '3' or str_credit[1] == '4' or str_credit[1] == '5')):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID")