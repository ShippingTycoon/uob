#include <stdio.h>
#include <string.h>
#include <assert.h>

/* enum numeral {I=1, V=5, X=10, L=50, C=100, D=500, M=1000};
typedef enum numeral numeral; */

#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000

void test(void);
int romanToArabic(char *roman);
void symbol2num(char *roman, int length, int *romanNum);
int check_previous(char roman[], int i);

int main(int argc, char **argv)
{
    test();

    if(argc==2){
        printf("The roman numberal %s is equal to %d\n",
        argv[1], romanToArabic(argv[1]));
    }
    else{
        printf("ERROR: Incorrect usage, try e.g. %sXXI\n",
        argv[0]);
    }
    return 0;
}

void test(void)
{
    /*char tstring[256] = {'V', '\0'};
    assert(romanToArabic(tstring) == 5);*/
}

int romanToArabic(char *roman)
{
    int i, sum = 0;
    int romanNum[50];
    int length = strlen(roman);
    symbol2num(roman, length, romanNum);
    for(i=0; i<length; i++){
        if(i<1){
            sum+=romanNum[i];
        }
        /* Problem is it doesn't matter which way round they are */
        else if((romanNum[i] == I) && (romanNum[i+1] == V || 
        romanNum[i+1] == X)){
            sum--;
        }
        else if((romanNum[i] == X) && (romanNum[i+1] == L || 
        romanNum[i+1] == C)){
            sum-=X;
        }
        else if((romanNum[i] == C) && (romanNum[i+1] == D || 
        romanNum[i+1] == M)){
            sum-=C;
        }
        else{
            sum+=romanNum[i];
        }
        printf("%d\n", sum);
    }
    return sum;
}

void symbol2num(char *roman, int length, int *romanNum)
{
    int i;
    /* Convert symbols to numbers */

    for(i=0; i<length; i++){
        switch(roman[i]){
            case 'I':
                romanNum[i] = I;
                break;
            case 'V':
                romanNum[i] = V;
                break;
            case 'X':
                romanNum[i] = X;
                break;
            case 'L':
                romanNum[i] = L;
                break;
            case 'C':
                romanNum[i] = C;
                break;
            case 'D':
                romanNum[i] = D;
                break;
            case 'M':
                romanNum[i] = M;
                break;
            default:
                printf("Input error.\n");
        }
    }
}