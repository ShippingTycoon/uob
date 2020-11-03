#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define SEQOFALPHA (('a'-1)*3)

enum bool {true, false};
typedef enum bool bool;

bool isvowel(char c);
bool isprime(int number);
void test(int t);

int main(void)
{
    int cnt=0;
    int n1, n2, n3;
    /*
    test();
    */
    for(n1='a';n1<='z';n1++){
        for(n2='a';n2<='z';n2++){
	    if (isvowel(n1) == true && isvowel(n2) == false){
		n3 = n1;
	        if (isprime(n1+n2+n3) == true){
		    cnt++;
		    printf("%3d %c%c%c\n",cnt, n1,n2, n3);
		}
	    }
	    if (isvowel(n1) == false && isvowel(n2) == true){
                n3 = n1;
                if (isprime(n1+n2+n3) == true){
                    cnt++;
                    printf("%3d %c%c%c\n",cnt, n1,n2, n3);
                }
            }
	}
    }
    return 0;	    
}

bool isvowel(char c)
{
    if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u'){
	return true;
    }
    else{
	return false;
    }
}

bool isprime(int number)
{
    int i;
    
    number = number - SEQOFALPHA;
    for (i=2;i<=sqrt(number);i++){
	 if (number % i == 0){
             return false;
	 }
    }
    return true;
}

void test(int t)

 {​​​​

     assert(isvowel(t) == true || isvowel(t) == false);

     assert(isprime(t) == true || isprime(t) == false);

 }​​​​
