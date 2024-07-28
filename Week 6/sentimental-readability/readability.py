# Readibility: implemented in python
from cs50 import get_string

text = get_string("Input text here: ")

# Count letters, words and sentences in the text
letters = 0
words = 1
sentences = 0
for _ in range(len(text)):
    if (text[_] >= 'a' and text[_] <= 'z') or (text[_] >= 'A' and text[_] <= 'Z'):
        letters += 1
    elif text[_] == '!' or text[_] == '?' or text[_] == '.':
        sentences += 1
    elif text[_] == ' ' or text[_] == '\0':
        words += 1

L = 100 / words * letters
S = 100 / words * sentences
ColemanLiau_Index = round(0.0588 * L - 0.296 * S - 15.8)
# Coleman Liau Index breakdown
if ColemanLiau_Index < 1:
    print("Before Grade 1")
elif ColemanLiau_Index > 16:
    print("Grade 16+")
else:
    print(f"Grade {ColemanLiau_Index}")
