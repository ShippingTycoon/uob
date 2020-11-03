#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LENGTH 20
#define GENERATIONS 50000000
#define INITIALCOST 24350

void test(void);
void init_board(int board[LENGTH]);
void change_board(int board[LENGTH]);
long calc_cost(int seq[LENGTH]);

int main(void)
{
    int board[LENGTH];
    int i;
    long cost = INITIALCOST;
    srand(time(NULL));
    init_board(board);
    test();
    for(i=0; i<GENERATIONS; i++){
        change_board(board);
        if(calc_cost(board)<cost){
            cost = calc_cost(board);
        }
    }
    printf("Total = %lu : ", cost);
    for(i=0; i<LENGTH; i++){
        printf("%d ", board[i]);
    }
    printf("\n");
    return 0;
}

long calc_cost(int seq[LENGTH])
{
    int i, j, k, minsum;
    long sum = 0;
    for(i=0; i<LENGTH; i++){
        j=i+1;
        if(j>=LENGTH){
            j-=LENGTH;
        }
        k=i+2;
        if(k>=LENGTH){
            k-=LENGTH;
        }
        minsum = seq[i] + seq[j] + seq[k];
        sum+=(int)pow(minsum, 2);
    }
    return sum;
}

void init_board(int board[LENGTH])
{
    int i;
    for(i=0; i<LENGTH; i++){
        board[i] = i+1;
    }
}

void change_board(int board[LENGTH])
{
    int a, b, tmp;
    a = rand()%LENGTH;
    b = rand()%LENGTH;
    tmp = board[a];
    board[a] = board[b];
    board[b] = tmp;
}

void test(void)
{
    int tboard[LENGTH];
    int tseq[LENGTH] = {0};
    init_board(tboard);
    assert(tboard[0] == 1);
    assert(tboard[LENGTH-1] == 20);
    assert(tseq[5] == 0);
}
