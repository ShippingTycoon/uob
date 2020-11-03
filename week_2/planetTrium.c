#include <stdio.h>

#define TOTAL_VOWELS 5
#define TOTAL_CONSONANTS 21

int main(void)
{
    char vowels[TOTAL_VOWELS] = {'a', 'e', 'i', 'o', 'u'};
    char consonants[TOTAL_CONSONANTS] = {'b', 'c', 'd', 'f',
    'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's',
    't', 'v', 'w', 'x', 'y', 'z'};
    
    int v, c1, c2;
    for (v=0; v<TOTAL_VOWELS; v++){
        for (c2=0; c2<TOTAL_CONSONANTS; c2++){
            for (c1=0; c1<TOTAL_CONSONANTS; c1++){
                printf("%c%c%c\n", consonants[c2], 
                vowels[v], consonants[c1]);
            }
        }
    }
    return 0;
}
