#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double approxPi(int squares, int circles);

#define RADIUS 50.0

int main(void)
{
    double i, x, y;
    double circles = 0;
    double pi;
    /* Choose random xy pairs from inside the square 
    and count the ones that fall in the circle */

    /* Get random xy values */
    for (i=0; i<100000000; i++){
        x = ((float)rand()/(float)(RAND_MAX)) * 50;
        y = ((float)rand()/(float)(RAND_MAX)) * 50;
        /* Does it fall in the circle? */
        if (pow(x, 2.0) + pow(y, 2.0) <= pow(RADIUS, 2.0)){
            circles++;
        }
    }

    pi = approxPi(i, circles);
    printf("%f\n", pi);
    return 0;
}

double approxPi(int squares, int circles)
{
    return ((double)(4*circles) / (double)squares);
}