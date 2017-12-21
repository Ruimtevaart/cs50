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
    int k = atoi(argv[1]);
    string s = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0, n = strlen(s); j < n; j++)
        {
            if ((96 < s[j] && s[j] < 123) || (64 < s[j] && s[j] < 91))
            {
                if (isupper(s[j]))
                {
                    char ci = ((((s[j] + k) - 65) % 26) + 65);
                    printf("%c", ci);
                }
                if (islower(s[j]))
                {
                    char ci = ((((s[j] + k) - 97) % 26) + 97);
                    printf("%c", ci);
                }
            }
            else
            {
                printf("%c", s[j]);
            }
        }
        printf("\n");
    }
    return 0;
}