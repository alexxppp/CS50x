# mario-more: implemented in python
while True:

    try:
        height = int(input("Height: "))
    except ValueError:
        print("Invalid input. Please enter an integer.")
        continue
    if 0 < height < 9:
        break

for rows in range(height):
    for spaces in range(height - rows - 1):
        print(" ", end="")

    for squares in range(rows + 1):
        print("#", end="")

    print("  ", end="")

    for aftersquares in range(rows + 1):
        print("#", end="")
    # /n
    print()
