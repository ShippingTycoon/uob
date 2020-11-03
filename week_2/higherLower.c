#include <stdio.h>
#include <stdlib.h>

enum result {correct, incorrect};
typedef enum result result;

int generate_secret_number(void);
int getGuess(void);
result checkGuess(int number_guess, int secret_number);
void higherLower(int number_guess, int secret_number);
void keepPlaying(int remaining_tries);

#define HIGHEST_NUMBER 1000
#define STARTING_TRIES 10
#define SECTRET_NUMBER (rand() % 1001)

int main(void)
{
    int rem_tries, number_guess;
    int secret_number = SECTRET_NUMBER;
    result answer;
    for(rem_tries = 10; rem_tries > 0; rem_tries--){
        printf("you have %d tries remaining.\n", rem_tries);
         /* User guesses number */
        number_guess = getGuess();
        /* Is the answer correct? */
        answer = checkGuess(number_guess, secret_number);
        switch(answer){
            case correct:
                printf("You won! Very well done.\n");
                return 0;
                break;
            case incorrect:
                printf("Wrong! ");
                higherLower(number_guess, secret_number);
                break;
        }
    }
    printf("Sorry, you're out of tries! The number was"
    "%d\n", secret_number);
    return 0;
}

int generate_secret_number(void)
{
    return rand() % HIGHEST_NUMBER + 1;
}

int getGuess(void)
{
    int guess;
    printf("Please guess a number ");
    if(scanf("%d", &guess) == 1){
        return guess;
    }
    else{
        printf("Something went wrong!\n");
        exit(1);
    }
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

/* Higher or lower than secret number */
void higherLower(int number_guess, int secret_number)
{
    if(number_guess > secret_number){
        printf("That was larger than the secret number.\n");
    }
    else{
        printf("That was lower than the secret number.\n");
    }
}