#include <stdio.h>
#include <assert.h>

void test(void);
void int2string(int i, char s[]);
int neg_to_pos(int i);
void reverse(char s[], int leng);

int main(void)
{
    int i;
    char s[256] = {0};

    test();

    scanf("%d", &i);
    int2string(i,s);
    printf("%s\n",s);
    return 0;
}

void test(void)
{
    assert(neg_to_pos(-5) == 5);
}

void int2string(int i, char s[])
{
    int j, k = 0;sc
    if(i<0){
        neg_to_pos(i);
    }
    while(i>10){
        j = i % 10;
        i /= 10;
        s[k] = j + '0';
        k++;
    }
    s[k] = i + '0';
    s[k+1] = '\0';
    reverse(s, k);
}

int neg_to_pos(int i)
{
    return i *= -1;
    printf("-");
}

void reverse(char s[], int leng)
{
    int i;
    char tmp;
    for(i=0; i<(leng/2); i++){
        tmp = s[i];
        s[i] = s[leng-i];
        s[leng-i] = tmp;
    }
}