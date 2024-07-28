#include <cs50.h>
#include <math.h>
#include <stdio.h>

int checkAuthenticity(long creditNumber);

int main(void)
{
    long creditNumber = get_long("Credit card number: ");
    if (checkAuthenticity(creditNumber) == 0 || creditNumber < 1)
    {
        printf("INVALID\n");
    }
    else if (checkAuthenticity(creditNumber) == 1)
    {
        printf("VISA\n");
    }
    else if (checkAuthenticity(creditNumber) == 2)
    {
        printf("MASTERCARD\n");
    }
    else if (checkAuthenticity(creditNumber) == 3)
    {
        printf("AMEX\n");
    }
}

int checkAuthenticity(long creditNumber)
{
    int totalNumbers = 0;
    int sum = 0;
    long temp = creditNumber;

    while (temp > 0)
    {
        int singleNumber = temp % 10;
        temp = temp / 10;
        totalNumbers++;

        if (totalNumbers % 2 == 0)
        {
            singleNumber = singleNumber * 2;
            if (singleNumber > 9)
            {
                singleNumber -= 9;
            }
        }
        sum += singleNumber;
    }

    int output = 0;
    if (sum % 10 == 0)
    {
        int firstTwoDigits = (int)(creditNumber / pow(10, totalNumbers - 2));
        int firstDigit = (int)(creditNumber / pow(10, totalNumbers - 1));

        if ((firstTwoDigits == 34 || firstTwoDigits == 37) && totalNumbers == 15)
        {
            output = 3;
        }
        else if ((firstTwoDigits >= 51 && firstTwoDigits <= 55) && totalNumbers == 16)
        {
            output = 2;
        }
        else if ((firstDigit == 4) && (totalNumbers == 13 || totalNumbers == 16))
        {
            output = 1;
        }
    }
    return output;
}
