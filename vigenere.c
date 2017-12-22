#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Invalid amount of command line arguements, stopping program...\n");
        return 1;
    }

    //issiaiskina ar key nera skaicius
    for (int c = 0; c < strlen(argv[1]); c++)
    {
        if ((argv[1][c] - 57) <= 0)
        {
            return 1;
        }
    }

    //gauna stringa
    string s = get_string("plaintext: ");
    printf("ciphertext: ");
    int a = 0, ab;

    //cikla kartoja tiek kartu kokio ilgio yra ivestas stringas
    for (int i = 0; i < strlen(s); i++)
    {

        //issiaiskina ar tikrinamas char nera simbolis
        if ((96 < s[i] && s[i] < 123) || (64 < s[i] && s[i] < 91))
        {
            //issiaiskina ar kintamasis a nera key ilgio, o jeigu jis yra, vel permeta i pimra key raide
            if (a == strlen(argv[1]))
            {
                a = 0;
            }
            if (isupper(argv[1][a]))
            {
                ab = (argv[1][a] - 65);
            }
            else
            {
                ab = (argv[1][a] - 97);
            }
            if (isupper(s[i]))
            {
                char ci = ((((s[i] + ab) - 65) % 26) + 65);
                printf("%c", ci);
            }
            if (islower(s[i]))
            {
                char ci = ((((s[i] + ab) - 97) % 26) + 97);
                printf("%c", ci);
            }
        }
        else
        {
            printf("%c", s[i]);
        }
        a++;
    }
    printf("\n");
    return 0;
}