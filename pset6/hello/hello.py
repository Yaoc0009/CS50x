from cs50 import get_string

def main():

    # Request user input
    name = get_string("What is your name? ")

    # say hello
    print(f"hello, {name}")


if __name__ == "__main__":
    main()

