#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Invalid amount of command line arguements, stopping program...\n");
        return 1;
    }
    char salt[3];
    strncpy(salt, argv[1], 2);
    char key[6];
    string answer;
    string symbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //tikrina slaptazodzius a-Z
    for (int a = 0; a < 52; a++)
    {
        key[0] = symbols[a];
        answer = crypt(key, salt);
        if (strcmp(answer, argv[1]) == 0)
        {
            printf("%s\n", key);
            return 0;
        }
    }
    //tikrina slaptazodzius aa-ZZ
    for (int b = 0; b < 52; b++)
    {
        key[0] = symbols[b];
        answer = crypt(key, salt);
        if (strcmp(answer, argv[1]) == 0)
        {
            printf("%s\n", key);
            return 0;
        }
        for (int c = 0; c < 52; c++)
        {
            key[1] = symbols[c];
            answer = crypt(key, salt);
            if (strcmp(answer, argv[1]) == 0)
            {
                printf("%s\n", key);
                return 0;
            }
        }
    }
    //tikrina slaptazodzius aaa-ZZZ
    for (int d = 0; d < 52; d++)
    {
        key[0] = symbols[d];
        answer = crypt(key, salt);
        if (strcmp(answer, argv[1]) == 0)
        {
            printf("%s\n", key);
            return 0;
        }
        for (int e = 0; e < 52; e++)
        {
            key[1] = symbols[e];
            answer = crypt(key, salt);
            if (strcmp(answer, argv[1]) == 0)
            {
                printf("%s\n", key);
                return 0;
            }
            for (int f = 0; f < 52; f++)
            {
                key[2] = symbols[f];
                answer = crypt(key, salt);
                if (strcmp(answer, argv[1]) == 0)
                {
                    printf("%s\n", key);
                    return 0;
                }
            }
        }
    }
    //tikrina slaptazodzius aaaa-ZZZZ
    for (int g = 0; g < 52; g++)
    {
        key[0] = symbols[g];
        answer = crypt(key, salt);
        if (strcmp(answer, argv[1]) == 0)
        {
            printf("%s\n", key);
            return 0;
        }
        for (int h = 0; h < 52; h++)
        {
            key[1] = symbols[h];
            answer = crypt(key, salt);
            if (strcmp(answer, argv[1]) == 0)
            {
                printf("%s\n", key);
                return 0;
            }
            for (int i = 0; i < 52; i++)
            {
                key[2] = symbols[i];
                answer = crypt(key, salt);
                if (strcmp(answer, argv[1]) == 0)
                {
                    printf("%s\n", key);
                    return 0;
                }
                for (int j = 0; j < 52; j++)
                {
                    key[3] = symbols[j];
                    answer = crypt(key, salt);
                    if (strcmp(answer, argv[1]) == 0)
                    {
                        printf("%s\n", key);
                        return 0;
                    }
                }
            }
        }
    }
    //tikrina slaptazodzius aaaaa-ZZZZZ
    for (int k = 0; k < 52; k++)
    {
        key[0] = symbols[k];
        answer = crypt(key, salt);
        if (strcmp(answer, argv[1]) == 0)
        {
            printf("%s\n", key);
            return 0;
        }
        for (int l = 0; l < 52; l++)
        {
            key[1] = symbols[l];
            answer = crypt(key, salt);
            if (strcmp(answer, argv[1]) == 0)
            {
                printf("%s\n", key);
                return 0;
            }
            for (int m = 0; m < 52; m++)
            {
                key[2] = symbols[m];
                answer = crypt(key, salt);
                if (strcmp(answer, argv[1]) == 0)
                {
                    printf("%s\n", key);
                    return 0;
                }
                for (int n = 0; n < 52; n++)
                {
                    key[3] = symbols[n];
                    answer = crypt(key, salt);
                    if (strcmp(answer, argv[1]) == 0)
                    {
                        printf("%s\n", key);
                        return 0;
                    }
                    for (int o = 0; o < 52; o++)
                    {
                        key[4] = symbols[o];
                        answer = crypt(key, salt);
                        if (strcmp(answer, argv[1]) == 0)
                        {
                            printf("%s\n", key);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}