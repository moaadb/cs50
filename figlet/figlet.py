from pyfiglet import Figlet
from random import randint
import sys

figlet = Figlet()
fonts = figlet.getFonts()

font = fonts[randint(0,425)]

input = input("Input: ")

if len(sys.argv) == 1:
    print(f"{font}")
    figlet.setFont(font=font)
    print("Output: ")
    print(figlet.renderText(input))
    sys.exit(0)

if len(sys.argv) == 3:
    if ("f" or "font" in sys.argv[1]) and sys.argv[2] in fonts:
        figlet.setFont(font=sys.argv[2])
        print("Output: ")
        print(figlet.renderText(input))
        sys.exit(0)
    else:
        print("Invalid usage")
        sys.exit(1)

print("Invalid usage")
sys.exit(1)