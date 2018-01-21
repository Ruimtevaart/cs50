// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int s = fraction[0] - '0';
    int v = fraction[2] - '0';
    int dur;
    if (v == 8)
    {
        dur = s;
    }
    else if (s > 1)
    {
        dur = 8 / v * s;
    }
    else
    {
        dur = 8 / v;
    }
    return dur;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    double n = 0;
    switch (note[0])
    {
        case 'C' :
            n = n - 9;
            break;
        case 'D' :
            n = n - 7;
            break;
        case 'E' :
            n = n - 5;
            break;
        case 'F' :
            n = n - 4;
            break;
        case 'G' :
            n = n - 2;
            break;
        case 'B' :
            n = n + 2;
            break;
        default :
            break;
    }
    switch (note[1])
    {
        case '#' :
        {
            if (note[0] == 'B' || note[0] == 'E')
            {
                int a = note[2] - '0';
                n = (n + 2) + ((a - 4) * 12);
                break;
            }
            else
            {
                int a = note[2] - '0';
                n = (n + 1) + ((a - 4) * 12);
                break;
            }
        }
        case 'b' :
        {
            if (note[0] == 'C' || note[0] == 'F')
            {
                int a = note[2] - '0';
                n = (n - 2) + ((a - 4) * 12);
                break;
            }
            else
            {
                int a = note[2] - '0';
                n = (n - 1) + ((a - 4) * 12);
                break;
            }
        }
        default :
        {
            int a = note[1] - '0';
            n = n + ((a - 4) * 12);
            break;
        }
    }
    double freq = round(440 * (pow(2, (n / 12))));
    return freq;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "\0") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
