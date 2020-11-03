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
void calc_soundex(char word[], char soundex[]);
codex_cases code_number(char c);
bool hw_rule(codex_cases a, char b, codex_cases c);
void fill_array()

int main(int argc, char **argv)
{
    char soundex[SOUNDEX_LENGTH] = {'0', '0', '0', '0', '\0'};
    test();
    if(argc==2){
        int *p = NULL;
        p = (int *)malloc(sizeof(char)*argv[1]);
        fill_array(p);
        calc_soundex(argv[1], soundex);
        printf("%s\n", soundex);
    }
    else{
        printf("ERROR, incorrect usage.\n");
    }    
    return 0;
}

void test(void)
{
    assert(code_number('B')==labial);
    assert(code_number('M')==nasal);
    assert(code_number('A')==skip);
    assert(code_number('N')==nasal);
    assert(code_number('G')==gutterals_sibilants);
    assert(hw_rule(labial, 'H', labial)==true);
    assert(hw_rule(nasal, 'G', dental)==false);
}

/* ? Make letter arrays for categories-labial, gutterals? */

void calc_soundex(char word[], char soundex[])
{
    int i, s_len, j=1;
    codex_cases code, next_code, next_next_code;
    int length = strlen(word);
    for()

    soundex[0] = toupper(word[0]);
    

    /* The next_code and next_next_code eventually go out of bounds */
    for(i=0; i<length-3; i++){
        code = code_number(word[i+1]);
        next_code = code_number(word[i+2]);
        next_next_code = code_number(word[i+3]);
        /* If next item is same codex, discard that codex */
        /* If 2 same codex positions seperated by only 'h' or
        'w', use first example of codex & discard second, but 
        not the 'h' or 'w' respectively */
        if(code!=skip && code!=next_code && 
        hw_rule(code, word[i+2], next_next_code)==false &&
        j<4){
            soundex[j] = code;
            j++;
        }
    }
    if(i==length-2 && code!=skip && code!=next_code && j<4){
        soundex[j] = code;
        j++;
        printf("%d, %d\n", i, code);
    }
    i++;
    if(i==length-1 && j<4){
        soundex[j] = code;
    }
    else{
        soundex[j] = '0';
    }

    /* If code longer than 4, rest are thrown away 
    s_len = strlen(soundex);
    if(s_len>SOUNDEX_LENGTH-1){
        soundex[SOUNDEX_LENGTH-1] = '\0';
    }*/
}

/* Test string agains conditions */
codex_cases code_number(char c)
{
    c = toupper(c);
    switch(c){
        case'B':
        case'F':
        case'P':
        case'V':
            return labial;
            break;
        case'c':
        case'G':
        case'J':
        case'K':
        case'Q':
        case'S':
        case'X':
        case'Z':
            return gutterals_sibilants;
            break;
        case'D':
        case'T':
            return dental;
            break;
        case'L':
            return long_liquid;
            break;
        case'M':
        case'N':
            return nasal;
            break;
        case'R':
            return short_liquid;
            break;
        case'A':
        case'E':
        case'H':
        case'I':
        case'O':
        case'U':
        case'W':
        case'Y':
            return skip;
            break;
        default:
            return skip;
            break;
    }
}

bool hw_rule(codex_cases a, char b, codex_cases c)
{
    if(a==c && a!=skip && (b=='H' || b=='W')){
        return true;
    }
    else{
        return false;
    }
}