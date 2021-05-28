#include <stdio.h>
#include <cs50.h>
#include <math.h>

int checkSum(long n);

int main(void)
{
    long cc_num = 0;

    // Retrieve user input
    do
    {
        cc_num = get_long("Number: ");
    }
    while (cc_num != (long) cc_num); // While cc_num is not a long type numeral

    // Check if numbers have valid number of digits
    if (cc_num < pow(10, 12) || cc_num > pow(10, 16) - 1)
    {
        printf("INVALID\n");
        return (0);
    }

    // Checksum to validate credit card numbers
    if (checkSum(cc_num) == 0)
    {
        // Check credit card companies based on signature
        if (cc_num / (long) pow(10, 13) == 34 || cc_num / (long) pow(10, 13) == 37)
        {
            printf("AMEX\n");
        }
        else if (cc_num / (long) pow(10, 14) > 50 && cc_num / (long) pow(10, 14) < 56)
        {
            printf("MASTERCARD\n");
        }
        else if (cc_num / (long) pow(10, 12) == 4 || cc_num / (long) pow(10, 15) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

int checkSum(long n)
{
    int sum = 0;
    int i = 0;

    while (i < 16)
    {
        // Sum odd position digits from the back
        if (i % 2 == 0)
        {
            sum += n % 10;
        }
        // Multiply by 2 and add digits together for even position digits
        else
        {
            int num = (n % 10) * 2;
            sum += num % 10 + num / 10;
        }
        // Remove last digit after summing each digit
        n /= 10;
        i++;
    }
    return sum % 10;
}