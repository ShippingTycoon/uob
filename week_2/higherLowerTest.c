#include <stdio.h>

enum result {correct, incorrect};
typedef enum result result;

int generate_secret_number(void);
int getGuess(int remaining_tries);
result checkGuess(int number_guess, int secret_number);
void higherLower(int number_guess, int secret_number);

#define HIGHEST_NUMBER 1000
#define STARTING_TRIES 10
#define SECTRET_NUMBER rand() HIGHEST_NUMBER + 1

int main(void)
{
    int remaining_tries = STARTING_TRIES;
    int secret_number, number_guess;
    result answer;
    /* Select random number */
    secret_number = generate_secret_number();
    /* User guesses number */
    number_guess = getGuess();
    /* Is the answer correct? */
    answer = checkGuess(number_guess, secret_number);
    switch(answer){
        case correct:
        printf("You won! Very well done.\n");
        break;
        case incorrect:
        remaining_tries--;
        printf("Wrong! ");
        higherLower(number_guess, secret_number);
        while(tries > 0){
            getGuess();
        }
    }
    /* Higher or lower than secret number */
    return 0;
}

int generate_secret_number(void)
{
    return rand() % HIGHEST_NUMBER + 1;
}

int getGuess(int remaining_tries)
{
    int guess;
    printf("Please guess a number, you have %d tries" 
    "remaining.\n", remaining_tries);
    scanf("%d", &guess);
    return guess;
}

result checkGuess(int number_guess, int secret_number)
{
    if(number_guess == secret_number){
        return correct;
    }
    else{
        return incorrect;
    }
}

void higherLower(int number_guess, int secret_number)
{
    if(number_guess > secret_number){
        printf("That was larger than the secret number.\n");
    }
    else{
        printf("That was lower than the secret number");
    }
}