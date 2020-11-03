#include <stdio.h>
#include <math.h>

int type(int x, int y, int z);
int longest(int a, int b, int c);
int right_angle(int a, int b, int c);

int main(void)
{
    int a, b, c;
    printf("Please enter three numbers to represent sides of a triangle: ");

    if (scanf("%d%d%d", &a, &b, &c) == 3)
    {
        if (a == -999)
        {
            return 0;
        }
        if (a<=0 || b<=0 || c<=0)
        {
            printf("Please use three positive integers.\n");
            main();
        }
        type(a, b, c);
    }
    else
    {
        printf("Usage: Enter three positive integers separated by a space and press enter.\n\n");
    }
    return 0;
}

int type(int x, int y, int z)
{
    if (x==y && y == z)
    {
        printf("\nThe lengths you have given represent an equilateral triangle.\n");
    }
    else if ((x == y && y != z) || (y == z && z != x))
    {
        printf("\nThe lengths you have given represent an isoceles triangle.\n");
        longest(x,y,z);
    }
    else if (x != y && y != z && z != x)
    {
        printf("\nThe lengths you have given represent a scalene triangle.\n");
        longest(x,y,z);
    }
    main();
    return 0;
}

int longest(int a, int b, int c)
{
    int longest = a;
    if (b>a)
    {
        longest = b;
    }
    if (c>b)
    {
        longest = c;
    }
    if (longest == a)
    {
        right_angle(longest, b, c);
    }
    else if (longest == b)
    {
        right_angle(longest, a, c);
    }
    else if (longest == c)
    {
        right_angle(longest, b, a);
    }
    return 0;
}

int right_angle(int longest, int b, int c)
{
    int toSquareRt = pow(b, 2) + pow(c, 2);
    
    double test;

    test = sqrt(toSquareRt);

    if(longest == test)
    {
        printf("\n...It's also a right angle triangle!\n");
    }
    else
    {
        printf("\n...It is not a right angle triangle.\n");
    }
    
    return 0;
}