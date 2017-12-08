#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Height: ");
    int height=get_int();
    while(height>23||height<0)
    {
        printf("Invalid height, please enter another one (between 1 and 23) ");
        height=get_int();
    }
    if (height==0)
    {
        return 0;
    }
    for(int i=0; i<height; i++)
    {
        int a, b, c;
        for(a=0; a<height-i-1; a++)
        printf(" ");
        for(b=0; b<height-a; b++)
        printf("#");
        printf("  ");
        for(c=0; c<b; c++)
        printf("#");
        printf("\n");
    };
}