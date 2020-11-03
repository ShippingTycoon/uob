#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

enum oddEven {odd, even};
typedef enum oddEven oddEven;

double getBalance(void);
void takeBet(double balance);
void placeBet(double bet, double balance);
void rouletteNumber(int number, double bet, double balance);
void rouletteOddEven(double bet, oddEven choice, double balance);
void win(double bet, double balance, bool winBig);
void lose(double bet, double balance);
int keepPlaying(double balance);
int generateNumber(void);

#define INITIAL_BALANCE 10.0
#define HIGHEST_NUMBER 35
#define BIG_WIN 34

int main(void)
{
    double balance = getBalance();
    takeBet(initialBalance);
    return 0;
}

double getBalance(void)
{
    double balance;
    printf("Welcome to Roulette!\nHow much money do you"
           " have?\n");
    while (scanf("%lf", balance) != 1 || balance < 0.01){
                while ((c = getchar()) != '\n' && c != EOF){
            /* discard */ ;
        }
        printf("Usage: 00.00 (positive number)\n");
    }
    return balance;
}

void takeBet(double balance)
{
    double  bet;
    char c;
    printf("You have £%.2lf to bet\n", balance);
    printf("How much would you like to bet? £");
    if (scanf("%lf", &bet) != 1){
        /* Solution to multiple inputs from user found at:
        http://c-faq.com/stdio/stdinflush2.html */
        while ((c = getchar()) != '\n' && c != EOF){
            /* discard */ ;
        }
        printf("Usage: 00.00\n");
        takeBet(balance);
    }
    else if (bet < 0.01){
        printf("Please enter a positive number as a bet!\n");
        takeBet(balance);
    }
    if (bet > balance){
        printf("Not enough money!\n");
        takeBet(balance);
    }
    placeBet(bet, balance);
}

void placeBet(double bet, double balance)
{
    int number;
    oddEven choice;
    char oddEven = 0;
    printf("Where would you like to place this bet?\n"
           "Your choices are the numbers 0 - 35, or simply"
           "type the letter \"o\" for odd or \"e\" for even.\n"
           "Your choice: ");

    if ((scanf("%d", &number)) == 1){
        if (number < 0 || number > HIGHEST_NUMBER){
            printf("Incorrect input: Min = 0, Max = 35\n");
            placeBet(bet, balance);
        }
        rouletteNumber(number, bet, balance);
    }
    oddEven = getchar();
    if (oddEven > 0){
        if (oddEven != 'o' && oddEven != 'e'){
            printf("Usage: \"o\" or \"e\"\n");
            placeBet(bet, balance);
        }
        else if (oddEven == 'e'){
            /* Setting the odd/even input to a number outside of
            normal betting in order to use roulette function */
            choice = even;
            rouletteOddEven(bet, choice, balance);
        }
        else{
            choice = odd;
            rouletteOddEven(bet, choice, balance);
        }

    }
}

/* If user input a number to bet on */
void rouletteNumber(int number, double bet, double balance)
{
    int result = generateNumber();
    printf("Result: %d\n", result);
    if (number == result){
      bool winBig = true;
      win(bet, balance, winBig);
    }
    else if (number != result){
        lose(bet, balance);
    }
}

/* If user placed their bet on either odd or even */
void rouletteOddEven(double bet, oddEven choice, double balance)
{
    int result = generateNumber();
    printf("Result: %d\n", result);
    bool winBig = false;

    switch(choice){
    case even:
        if (result%2 == 0 && result != 0){
            win(bet, balance, winBig);
        }
        else{
            lose(bet, balance);
        }
        break;
    case odd:
        if (result%2 == 0 && result != 0){
            win(bet, balance, winBig);
        }
        else{
            lose(bet, balance);
        }
        break;
    }
}

/* Simulate the roulette wheel */
int generateNumber(void)
{
    srand(time(NULL));
    /* Mod 36 (HIGHEST_NUMBER + 1) gives the rand function
    the upper bound of 35 */
    return (rand() % (HIGHEST_NUMBER + 1));
}

void win(double bet, double balance, bool winBig)
{
    if (winBig == true){
      bet *= BIG_WIN;
    }
    printf("You won £%.2lf!\n", bet);
    balance += bet;
    printf("Your new balance is £%.2lf\n", balance);
    keepPlaying(balance);
}

void lose(double bet, double balance)
{
    printf("You lose!");
    balance -= bet;
    printf("\nYour new balance is £%.2lf\n", balance);
    if (balance <= 0){
        printf("You're out of money!\n");
        exit(0);
    }
    keepPlaying(balance);
}

int keepPlaying(double newBalance)
{
    char playOn = 0, c;
    printf("Keep playing? (y/n) : ");
    while ((c = getchar()) != '\n' && c != EOF){
        /* discard */ ;
    }
    playOn = getchar();
    
    if (playOn != 'y' && playOn != 'n'){
        printf("Usage: Enter \"y\" or \"n\"\n");
        keepPlaying(newBalance);
    }

    if (playOn == 'y'){
        while ((c = getchar()) != '\n' && c != EOF){
            /* discard */ ;
        }
        takeBet(newBalance);
        return 0;
    }
    else if (playOn == 'n'){
        exit(0);
    }
}
