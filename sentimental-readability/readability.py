# TODO
from cs50 import get_string

letters = 0
words = 0
sentences = 0

text = get_string("Input: ")
text = text.lower()

for i in range(len(text)):
    if text[i] >= "a" and text[i] <= "z":
        letters += 1
    if text[i] == " " or i == len(text) - 1:
        words += 1
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

L = letters / words * 100
S = sentences / words * 100

index = 0.0588 * L - 0.296 * S - 15.8
index = round(index)

if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {index}")
