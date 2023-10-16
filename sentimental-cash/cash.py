# TODO
from cs50 import get_float

QUARTER = 0.25
DIME = 0.10
NICKEL = 0.05
PENNY = 0.01

change = 0

quarters = 0
dimes = 0
nickels = 0
pennies = 0

count = 0

while change < 0.01:
    change = get_float("Change owed: ")

# count quarters

while change >= QUARTER:
    quarters += 1
    change -= QUARTER
    change = round(change, 2)

while change >= DIME:
    dimes += 1
    change -= DIME
    change = round(change, 2)

while change >= NICKEL:
    nickels += 1
    change -= NICKEL
    change = round(change, 2)

while change >= PENNY:
    pennies += 1
    change -= PENNY
    change = round(change, 2)

total = quarters + dimes + nickels + pennies
print(total)
