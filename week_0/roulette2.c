#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>
#include <assert.h>

enum typeOfBet {odd, even, num};
typedef enum typeOfBet typeOfBet;

double getBalance(void);
double takeBet(double balance);
typeOfBet BetType(double bet, double balance);
int generateNumber(void);
int getNumber(void);
bool rouletteOddEven(int result, typeOfBet choice);
double win(double bet, double balance, int multiplier, int result);
double lose(double bet, double balance, int result);
void keepPlaying(void);

#define HIGHEST_NUMBER 35
#define NUMBER_MULTIPLIER 34
#define ODD_EVEN_MULTIPLIER 1

int main(void)
{
    static double balance;
    if (balance == 0){
        balance = getBalance();
    }
    assert(balance >= 0.01);

    double bet = takeBet(balance);
    assert(bet>0.01 && bet<balance);

    typeOfBet choice = BetType(bet, balance);
    assert(choice == odd || choice == even || choice == num);

    int result = generateNumber();
    assert(result >= 0 && result <= HIGHEST_NUMBER);

    bool oddEvenWin;
    bool numWin;
    int number;
    switch(choice){
        case odd ... even:
            oddEvenWin = rouletteOddEven(result, choice);
                if (oddEvenWin == true){
                    balance = win(bet, balance, 
                    ODD_EVEN_MULTIPLIER, result);
                }
                else{
                    balance = lose(bet, balance, result);
                }
            break;
        case num:
            number = getNumber();
            numWin = false;
            if (number == result){
                numWin = true;
                balance = win(bet, balance, 
                NUMBER_MULTIPLIER, result);
            }
            else{
                balance = lose(bet, balance, result);
            }
    }

    keepPlaying();

    return 0;
}

/* Prompt user to set up their wallet initial balance */
double getBalance(void)
{
    double balance;
    char c;
    printf("Welcome to Roulette!\nHow much money do you"
           " have?\n£");
    while (scanf("%lf", &balance) != 1 || balance < 0.01){
        fflush(stdin);
        return 0;
    }
    return balance;
}

/* Find out how much the user would like to bet */
double takeBet(double balance)
{
    double  bet;
    char c;
    printf("You have £%.2lf to bet\n", balance);
    printf("How much would you like to bet? £");
    if (scanf("%lf", &bet) != 1){
        while ((c = getchar()) != '\n' && c != EOF){
            /* discard */ ;
        }
        printf("Usage: 00.00\n");
        takeBet(balance);
    }
    return bet;
}

/* Determine whether user will bet odd, even or a 
specific number */
typeOfBet BetType(double bet, double balance)
{
    typeOfBet choice;
    char oddEvenNum = 0;
    char c;
    printf("Where would you like to place this bet?\n"
           "type the letter \"o\" for odd, \"e\" for even,\n"
           "or \"n\" to bet on a single number.\n"
           "Your choice: ");
    while ((c = getchar()) != '\n' && c != EOF){
        /* discard */ ;
    }
    oddEvenNum = getchar();
    if (oddEvenNum > 0){
        if (oddEvenNum != 'o' && oddEvenNum != 'e' && 
            oddEvenNum != 'n'){
            printf("Usage: \"o\", \"e\" or \"n\"\n");
            return 0;
        }
        switch(oddEvenNum){
            case 'e':
                return even;
                break;
            case 'o':
                return odd;
                break;
            case 'n':
                return num;
                break;
        }
    }
}

/* Get a number to bet on from user */
int getNumber(void)
{
    int number;
    printf("Please choose a number to bet on: ");
    while ((scanf("%d", &number)) == 1){
        fflush(stdin);
        return number;
    }
}

/* Simulate the roulette wheel */
int generateNumber(void)
{
    int result;
    srand(time(NULL));
    /* Mod 36 (HIGHEST_NUMBER + 1) gives the rand function
    the upper bound of 35 */
    result = (rand() % (HIGHEST_NUMBER + 1));
    return result;
}

/* If user placed their bet on either odd or even */
bool rouletteOddEven(int result, typeOfBet choice)
{
    switch(choice){
    case even:
        if (result%2 == 0 && result != 0){
            return true;
        }
        else{
            return false;
        }
        break;
    case odd:
        if (result%2 == 0 && result != 0){
            return true;
        }
        else{
            return false;
        }
        break;
    }
}

/* Called if user wins to update balance */
double win(double bet, double balance, int multiplier, int result)
{
    printf("The number was %d\n", result);
    bet *= multiplier;
    printf("You won £%.2lf!\n", bet);
    balance += bet;
    printf("Your new balance is £%.2lf\n", balance);
    return balance;
}

/* Called if user loses to update balance */
double lose(double bet, double balance, int result)
{
    printf("The number was %d\n", result);
    printf("You lose!");
    balance -= bet;
    printf("\nYour new balance is £%.2lf\n", balance);
    if (balance <= 0){
        printf("You're out of money!\n");
        exit(0);
    }
    return balance;
}

/* Asks user if they want to exit or continue playing */
void keepPlaying(void)
{
    char playOn = 0, c;
    printf("Keep playing? (y/n) : ");
    while ((c = getchar()) != '\n' && c != EOF){
        /* discard */ ;
    }
    playOn = getchar();
    assert(playon == 'y' || playon == 'n');
    if (playOn == 'y'){
        fflush(stdin);
        main();
    }
    else if (playOn == 'n'){
        printf("Goodbye!\n");
    }
    exit(0);
}
