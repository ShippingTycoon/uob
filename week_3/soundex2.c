#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define SOUNDEX_LENGTH 5

enum codex_cases {labial='1', gutterals_sibilants='2', 
dental='3', long_liquid='4', nasal='5', short_liquid='6',
skip='0'};
typedef enum codex_cases codex_cases;

void test(void);
void fill_array(codex_cases p[], char word[]);

int main(int argc, char **argv)
{
    char soundex[SOUNDEX_LENGTH] = {'0', '0', '0', '0', '\0'};
    test();
    if(argc==2){
        codex_cases *p = NULL;
        p = (int *)malloc(sizeof(char*)argv[1]);
        fill_array(p, argv[1]);
        /*calc_soundex(argv[1], soundex);
        printf("%s\n", soundex);*/
    }
    else{
        printf("ERROR, incorrect usage.\n");
    }    
    return 0;
}

void test(void)
{
    char a1[10] = {'W', 'a', 's', 'h', 'i', 'n', 'g', 't',
    'o', 'n'};
    int cc1[10] = {0};
    fill_array(cc1, a1);
    assert(cc1 == {0, 0, 2, 0, 0, 5, 2, 3, 0, 5});
}

void fill_array(int p[], char word[])
{
    int i;
    for(i=0; i<strlen(word); i++){
        word[i] = toupper(word[i]);
        switch(word[i]){
            case'B':
            case'F':
            case'P':
            case'V':
                p[i] = labial;
                break;
            case'c':
            case'G':
            case'J':
            case'K':
            case'Q':
            case'S':
            case'X':
            case'Z':
                p[i] = gutterals_sibilants;
                break;
            case'D':
            case'T':
                p[i] = dental;
                break;
            case'L':
                p[i] = long_liquid;
                break;
            case'M':
            case'N':
                p[i] = nasal;
                break;
            case'R':
                p[i] = short_liquid;
                break;
            case'A':
            case'E':
            case'H':
            case'I':
            case'O':
            case'U':
            case'W':
            case'Y':
                p[i] = skip;
                break;
            default:
                p[i] = skip;
                break;
        }
    }
}