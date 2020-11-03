#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define SOUNDEXSIZE 3

void test(void);
void to_s_code(char w[], int codes[]);
void apply_scode_rules(int codes[], int l);
void condense_codes(int codes[], int s[], int l);

int main(int argc, char **argv)
{
    int soundex[SOUNDEXSIZE] = {0};
    int length, i;
    int *all_codes;
    test();

    if(argc==2){
        length = strlen(argv[1]);
        all_codes = (int *)malloc(length * sizeof(int));
        /* Turn the array into the codex */
        /* First digit is the upper case first letter */
        printf("%c", toupper(argv[1][0]));
        /* Convert the whole array to scode */
        to_s_code(argv[1], all_codes);
        /* Parse the scode to apply the special cases */
        apply_scode_rules(all_codes, length);
        condense_codes(all_codes, soundex, length);
        for(i=0; i<SOUNDEXSIZE; i++){
            printf("%d", soundex[i]);
        }
        printf("\n");
    }
    else{
        printf("ERROR: Incorrect usage.\n");
    }
    free(all_codes);
    return 0;
}

void to_s_code(char w[], int c[])
{
    int i;
    int l = strlen(w);
    for(i=0; i<l; i++){
        w[i] = toupper(w[i]);
        switch(w[i]){
            case'B':
            case'F':
            case'P':
            case'V':
                c[i] = 1;
                break;
            case'c':
            case'G':
            case'J':
            case'K':
            case'Q':
            case'S':
            case'X':
            case'Z':
                c[i] = 2;
                break;
            case'D':
            case'T':
                c[i] = 3;
                break;
            case'L':
                c[i] = 4;
                break;
            case'M':
            case'N':
                c[i] = 5;
                break;
            case'R':
                c[i] = 6;
                break;
            case'H':
            case'W':
                c[i] = 7;
                break;
            case'A':
            case'E':
            case'I':
            case'O':
            case'U':
            case'Y':
                c[i] = 0;
                break;
            default:
                c[i] = 0;
                break;
        }
    }
}

void apply_scode_rules(int codes[], int l)
{
    int i, j;
    for(i=0; i<(l-1); i++){
        if(codes[i] == codes[i+1]){
            codes[i+1] = 8;
        }
    }
    for(j=0; j<(l-3); j++){
        if(codes[j] == codes[j+2] && codes[j+1] == 7){
            codes[j+2] = 8;
        }
    }
}

void condense_codes(int codes[], int s[], int l)
{
    int i, j;
    i=0;
    j=1;
    while(i<SOUNDEXSIZE && j<l){
        if(codes[j] == 8 || codes[j] == 7 || codes[j] == 0){
            j++;
        }
        else{
            s[i] = codes[j];
            i++;
            j++;
        }
    }
}

void test(void)
{
    int i;
    int stest[SOUNDEXSIZE];
    char a1[] = "hello";
    char a2[] = "Pfister";
    int l = strlen(a1);
    int l2 = strlen(a2);
    int s1[5] = {7, 0, 4, 4, 0};
    int s2[7] = {1, 1, 0, 2, 3, 0, 6};
    int dummy[5] = {0};
    int d2[7];
    to_s_code(a1, dummy);
    for(i=0; i<5; i++){
        assert(dummy[i] == s1[i]);
    }
    to_s_code(a2, d2);
    for(i=0; i<l2; i++){
        assert(d2[i] == s2[i]);
    }
    apply_scode_rules(s1, 5);
    assert(s1[3] == 8);
    condense_codes(s1, stest, l);
    assert(stest[0] == 4);
}