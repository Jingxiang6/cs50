# import get_float function from cs50
from cs50 import get_float

# prompt the user to input a credit card number
while True:
    cash = get_float("Change owed: ")
    if cash > 0:
        break
# convert dollars to cents
cents = round(cash * 100)
# calculate the number of quarters
quarters = cents // 25
# calculate the number of dimes
dimes = (cents % 25) // 10
# calculate the number of nickels
nickels = ((cents % 25) % 10) // 5
# calculate the number of pennies
pennies = (((cents % 25) % 10) % 5) // 1

# print out the total number of coins
print(quarters + dimes + nickels + pennies)

