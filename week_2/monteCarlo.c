#include <stdio.h>
#include <math.h>
#include <stdlib.h>

enum landed {square, circle};
typedef enum landed landed;

landed throwDart(int x, int y);
double calculatePi(int squareCount, int circleCount);

#define RADIUS 50
#define SIDE_OF_SQUARE 50

int main(void)
{
    int x, y, squareCount = 0, circleCount = 0;
    double approxPi;
    for (x=0; x<50; x++){
        for (y=0; y<50; y++){
            /* Calculate numbers to determine if dart hit 
            square or circle */
            landed location = throwDart(x, y);
            /* Add result to square or circle counter */
            switch(location){
                case square:
                squareCount++;
                break;
                case circle:
                circleCount++;
                break;
            }
        }
    }
    printf("c = %d, s = %d", circleCount, squareCount);
    /* Approximate pi */
    approxPi = calculatePi(squareCount, circleCount);
    printf("%f\n", approxPi);
    return 0;
}

landed throwDart(int x, int y)
{
    if (pow(x, 2) + pow(y, 2) <= pow(RADIUS, 2)){
        return circle;
    }
    if (x <= SIDE_OF_SQUARE && y <= SIDE_OF_SQUARE){
        return square;
    }
    exit(1);
}

/* Choose random xy pairs from inside the square 
and count the pnes that fall in the circle */

double calculatePi(int squareCount, int circleCount)
{
    double pi;
    pi = (4*circleCount) / squareCount;
    return pi;
}