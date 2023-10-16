# TODO
from cs50 import get_int

n = 0
while n < 1 or n > 8:
    n = get_int("Height: ")

for i in range(n):
    print(" " * (n - i - 1), end="")
    for j in range(i + 1):
        print("#", end="")
    print()
