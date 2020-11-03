#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

enum day {sun, mon, tue, wed, thu, fri, sat};
typedef enum day day;

int main(void)
{
    assert(find_next_day(mon)== tue);
    assert(find_next_day(sat)==sun);
    assert(find_next_day(sun)==mon);
    return 0;
}

day find_next_day(day d)
{
    day next_day;
    switch(d)
    {
        case sun:
            return mon;
        case mon:
            return tue;
        case tue:
            return wed;
        case wed:
            return thu;
        case thu:
            return fri;
        case fri:
            return sat;
        case sat:
            return sun;   
    }
    printf("I wasn't expecting that!\n");
    exit(1);
}