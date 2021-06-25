from cs50 import get_int


def main():

    # Request user input
    num = get_int("Number: ")

    if checkSum(num):
        cardCompany(num)
    else:
        print("INVALID")

# Checksum with luhn's algorithm


def checkSum(num):

    sum = 0

    # Sum of digits with Luhn's algorithm
    for i, n in enumerate(reversed(str(num))):
        if i % 2 == 0:
            sum += int(n)
        else:
            for j in str(int(n) * 2):
                sum += int(j)

    # Check divisibility by 10
    if sum % 10 == 0:
        return True
    return False

# Function to check card company


def cardCompany(num):

    n = int(str(num)[0:2])
    l = len(str(num))
    
    # Check AMEX
    if n in [34, 37] and l == 15:
        print("AMEX")
    
    # Check MASTERCARD
    elif n in range(51, 56) and l == 16:
        print("MASTERCARD")
    
    # Check VISA
    elif n in range(40, 50) and (l == 13 or l == 16):
        print("VISA")
    
    # Else INVALID
    else:
        print("INVALID")
        
        
if __name__ == "__main__":
    main()