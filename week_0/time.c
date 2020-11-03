#include <stdio.h>

int main(void)
{
    int aHr, aMin, bHr, bMin;
    
    printf("Enter two times : ");
    if (scanf("%d:%d %d:%d", &aHr, &aMin, &bHr, &bMin) == 4)
    {
        if (aHr > 23 || bHr > 23 || aMin > 59 || bMin > 59)
        {
            printf("Usage: HH:MM HH:MM\n");
            return 0;
        }

        int aTime = (aHr*60) + aMin;
        int bTime = (bHr*60) + bMin;
        int dif, difHr, difMin;

        if (aTime > bTime)
        {
            aTime -= (24*60);
        }

        dif = bTime - aTime;
        difHr = dif/60;
        difMin = dif%60;
        
        printf("%d:%d %d:%d\n", aHr, aMin, bHr, bMin);
        printf("The difference is %d:%d\n", difHr, difMin);
    }

    return 0;
}