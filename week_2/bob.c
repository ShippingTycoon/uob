#include <stdio.h>

#define TOTAL_VOWELS 5
#define TOTAL_CONSONANTS 21

int isprime(int a, int b, int c);

int main(void)
{
    char vowels[TOTAL_VOWELS] = {'a', 'e', 'i', 'o', 'u'};
    char consonants[TOTAL_CONSONANTS] = {'b', 'c', 'd', 'f',
    'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's',
    't', 'v', 'w', 'x', 'y', 'z'};

    int c, v1, v2;
    for (v1=0; v1<TOTAL_VOWELS; v1++){
        for (v2=0; v2<TOTAL_VOWELS; v2++){
            for (c=0; c<TOTAL_CONSONANTS; c++){
                if (isprime(vowels[v2], consonants[c], 
                    vowels[v1]) == 1){
                    printf("%c%c%c\n", vowels[v2], 
                    consonants[c], vowels[v1]);
                }
            }
        }
    }
    int v, c1, c2;
    for (v=0; v<TOTAL_VOWELS; v++){
        for (c2=0; c2<TOTAL_CONSONANTS; c2++){
            for (c1=0; c1<TOTAL_CONSONANTS; c1++){
                if (isprime(consonants[c2], vowels[v], 
                    consonants[c1]) == 1){
                    printf("%c%c%c\n", consonants[c2], 
                    vowels[v], consonants[c1]);
                }
            }
        }
    }
    return 0;
}



int isprime(int a, int b, int c)
{
    int num = ((a % ('a'-1)) + (b % ('a'-1)) + (c % ('a'-1)));
    int i;
    /* Is number prime*/
    for (i = 2; i < num; i++)
    {
        if (num%i == 0)
        {
            return 0;
        }
    }
    return 1;
}