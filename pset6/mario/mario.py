from cs50 import get_int


def main():

    # Get user input for height
    while True:
        h = get_int("Height: ")
        if 1 <= h <= 8:
            break

    # Print lines
    for i in range(h):
        space(h - i - 1)
        sign(i + 1)
        space(2)
        sign(i + 1)
        print()

# Print spaces


def space(n):
    for _ in range(n):
        print(" ", end="")

    return

# Print spaces


def sign(n):
    for _ in range(n):
        print("#", end="")

    return


if __name__ == "__main__":
    main()