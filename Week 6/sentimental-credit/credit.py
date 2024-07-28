# credit: implemented in python
number = input("Credit number: ")

correct = False
AMEX = False
Visa = False
Mastercard = False
sum = 0

# Luhn's algorithm
for i in range(len(number) - 2, -1, -2):
    digit = int(number[i]) * 2
    if digit > 9:
        digit = digit - 9
    sum += digit

# Add the sum of the rest of the digits
for i in range(len(number) - 1, -1, -2):
    sum += int(number[i])

if sum % 10 == 0:
    correct = True

firstDigs = number[0] + number[1]

# Checking type of cc
if (firstDigs == "34" or firstDigs == "37") and len(number) == 15:
    AMEX = True
elif (firstDigs == "51" or firstDigs == "52" or firstDigs == "53" or firstDigs == "54" or firstDigs == "55") and len(number) == 16:
    Mastercard = True
elif firstDigs[0] == "4" and (len(number) == 16 or len(number) == 13):
    Visa = True
# breakdown
if correct:
    if AMEX:
        print("AMEX")
    elif Mastercard:
        print("MASTERCARD")
    elif Visa:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
