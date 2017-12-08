#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Enter your credit card number ");
    long long cardnum = get_long_long();
    while (cardnum < 0)
    {
        printf("Please enter another card number ");
        cardnum = get_long_long();
    }
    long long digits;
    int count;
    count = 0;
    digits = cardnum;
    while (digits > 0)
    {
        digits = digits / 10;
        count++;
    }
    if (count != 13 && count != 15 && count != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    long long step1;
    int sum1, num;
    sum1 = 0;
    step1 = cardnum;
    num = 0;
    while (step1 > 0)
    {
        num = (step1 / 10) % 10;
        num = num * 2;
        if (num >= 10)
        {
            num = (num % 10) + (num / 10);
        }
        sum1 = sum1 + num;
        step1 = step1 / 100;
    }
    long long step12;
    int sum2, sum;
    step12 = cardnum / 10;
    sum2 = cardnum % 10;
    num = 0;
    while (step12 > 0)
    {
        num = (step12 / 10) % 10;
        sum2 = sum2 + num;
        step12 = step12 / 100;
    }
    sum = sum1 + sum2;
    long long type;
    if (sum % 10 == 0)
    {
        if (count == 15)
        {
            for (int i = 0; i < 13; i++)
            {
                cardnum = cardnum / 10;
            }
            if (cardnum == 34 || cardnum == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (count == 13)
        {
            for (int j = 0; j < 12; j++)
            {
                cardnum = cardnum / 10;
            }
            if (cardnum == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (count == 16)
        {
            type = cardnum;
            for (int k = 0; k < 15; k++)
            {
                type = type / 10;
            }
            if (type == 4)
            {
                printf("VISA\n");
            }
            else
            {
                type = cardnum;
                for (int x = 0; x < 14; x++)
                {
                    type = type / 10;
                }
                if (type == 51 || type == 52 || type == 53 || type == 54 || type == 55)
                {
                    printf("MASTERCARD\n");
                }
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}