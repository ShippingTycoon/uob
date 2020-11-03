#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define DEFAULT_ARRAY_SIZE 100

void test(void);
void get_phrase(char arr[]);
int get_length(char phrase[]);
bool test_palindrome(char arr[], int arr_length);

int main(void)
{
    char pal[DEFAULT_ARRAY_SIZE] = {0};
    int phrase_length;
    bool palindrome = false;

    test();

    /* Prompt user for phrase */
    get_phrase(pal);

    /* Calculate length of array */
    phrase_length = get_length(pal);
    
    /* Test phrase is palindrome */
    palindrome = test_palindrome(pal, phrase_length);
    if(palindrome == true){
        printf("That is a palindrome.\n");
    }
    else{
        printf("That is not a palindrome.\n");
    }
    return 0;
}

void test(void)
{
    char test_array1[5] = {'a', 'b', 'c', 'd', '\0'};
    char test_array2[6] = {'k', 'a', 'y', 'a', 'k', '\0'};
    char test_array3[7] = {'h', 'a', 'n', 'n', 'a', 'h', 
    '\0'};
    assert(get_length(test_array1) == 4);
    assert(get_length(test_array3) == 6);
    assert(test_palindrome(test_array1, 4) == false);
    assert(test_palindrome(test_array2, 5) == true);
    assert(test_palindrome(test_array3, 6) == true);
    assert((test_palindrome*test_array3, 100) == false);
}

/* Parse phrase into array, removing all non-alpha chars */
void get_phrase(char arr[])
{
    printf("Type a phrase...\n");
    scanf("%s", arr);
}

int get_length(char phrase[])
{
    int cnt = 0;
    while(phrase[cnt] != '\0'){
        cnt++;
    }
    return cnt;
}

bool test_palindrome(char arr[], int arr_length)
{
    int i;
    for(i=0; i<arr_length; i++){
        if(arr[i] != arr[arr_length-(i+1)]){
            return false;
        }
    }
    return true;
}