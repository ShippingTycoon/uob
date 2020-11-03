/* Simple model of forest fires using cellular automation */
/* In the form of a 2D grid of cells */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "neillsimplescreen.h"

#define GENERATIONS 1000
#define BIRTHRATE 50
#define LIGHTNING 500
#define EMARG 0.7
#define TALL 30
#define WIDE 80
#define MINSIZE 6
#define EMPTY 0
#define TREE 1
#define FIRE 2
#define NOTFIRE 3
#define INCORRECT 4
#define FIRESYMBOL '*'
#define TREESYMBOL '@'
#define EMPTYSYMBOL ' '
#define WRONGSYMBOL '?'
#define WAITTIME 0.1

/* Test the program is working correctly */
void test(void);
/* Simulate the spreading of fire */
void fire_spread(int grid[TALL][WIDE]);
/* Check each cells 8 neighbours */
int check_8(int x, int y, int grid[TALL][WIDE]);
/* Reassign values of the grid to print */
void reassign(int grid[TALL][WIDE], int tmp[TALL][WIDE]);
/* Determine which cells will change state to TREE or FIRE*/
void birth_lightning(int grid[TALL][WIDE]);
/* Convert cells int value to corresponding printable char*/
char calc_char(int a);

int main(void)
{
    int grid[TALL][WIDE] = {0};
    int i, y, x;
    srand(time(NULL));
    test();
    neillclrscrn();
    neillcursorhome();
    for(i=0; i<GENERATIONS; i++){
        fire_spread(grid);
        birth_lightning(grid);
        for(y=0; y<TALL; y++){
            for(x=0; x<WIDE; x++){
                printf("%c", calc_char(grid[y][x]));
            }
            printf("\n");
        }
        neillcursorhome();
        neillbusywait(WAITTIME);
    }
    neillclrscrn();
    neillfgcol(white);
    return 0;
}

void fire_spread(int grid[TALL][WIDE])
{
    int y, x;
    int tmp[TALL][WIDE];
    /* Iterate through array */
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            tmp[y][x] = grid[y][x];
            /* Check each cells 8 neighbours */
            if(check_8(x, y, grid) == FIRE){
                tmp[y][x] = FIRE;
            }
        }
    }
    reassign(grid, tmp);
}

int check_8(int x, int y, int grid[TALL][WIDE])
{
    int i, j;
    for(i=y-1; i<=y+1; i++){
        for(j=x-1; j<=x+1; j++){
            /* Out of bounds check */
            if(i<0 || j<0 || i>=TALL || j>=WIDE){
                /* Skip */
            }
            else if(grid[i][j] == FIRE && 
            grid[y][x] == TREE){
                return FIRE;
            }
        }
    }
    return NOTFIRE;
}

void reassign(int grid[TALL][WIDE], int tmp[TALL][WIDE])
{
    int y, x;
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            /* Fire goes out */
            if(grid[y][x] == FIRE){
                grid[y][x] = EMPTY;
            }
            else{
                grid[y][x] = tmp[y][x];
            }
        }
    }
}

void birth_lightning(int grid[TALL][WIDE])
{
    int y, x;
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            if(grid[y][x] == EMPTY){
                /* Create tree */
                if(rand()%BIRTHRATE == 0){
                    grid[y][x] = TREE;
                }
            }
            else if(grid[y][x] == TREE){
                /* Create fire from lightning strike */
                if(rand()%LIGHTNING == 0){
                    grid[y][x] = FIRE;
                }
            }
        }
    }
}

char calc_char(int a)
{
    switch(a){
        case EMPTY:
            neillfgcol(black);
            return EMPTYSYMBOL;
        case TREE:
            neillfgcol(green);
            return TREESYMBOL;
        case FIRE:
            neillfgcol(red);
            return FIRESYMBOL;
        default:
            neillfgcol(yellow);
            return WRONGSYMBOL;
    }
}

void test(void)
{
    int y, x, i;    
    int tarr1[TALL][WIDE] = {0};
    int tarr2[TALL][WIDE] = {0};
    int tmp[TALL][WIDE] = {0};
    int tmp2[TALL][WIDE];
    int tmp3[TALL][WIDE];
    int tarr3[TALL][WIDE];
    int midx = WIDE/2;
    int midy = TALL/2;
    double tree_cnt = 0.0;
    double fire_cnt = 0.0;
    double exact;
    assert(TALL >= MINSIZE);
    assert(WIDE >= MINSIZE);
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            tmp2[y][x] = TREE;
        }
    }
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            assert(tmp2[y][x] == TREE);
        }
    }
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            tmp3[y][x] = FIRE;
        }
    }
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            assert(tmp3[y][x] == FIRE);
        }
    }
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            tarr1[y][x] = TREE;
        }
    }
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            assert(tarr1[y][x] == TREE);
        }
    }
    tarr1[midy][midx] = FIRE;
    /* Check_8 */
    for(y=midy-1; y<=midy+1; y++){
        for(x=midx-1; x<=midx+1; x++){
            if(y==midy && x==midx){
                assert(check_8(x, y, tarr1) == NOTFIRE);
            }
            else{
                assert(check_8(x, y, tarr1) == FIRE);
            }
        }
    }
    assert(check_8(midx-2, midy-2, tarr1) == NOTFIRE);
    assert(check_8(0, 0, tarr1) == NOTFIRE);
    fire_spread(tarr1);
    /* Fire spread */
    for(y=midy-1; y<=midy+1; y++){
        for(x=midx-1; x<=midx+1; x++){
            if(y==midy && x==midx){
                assert(tarr1[y][x] == EMPTY);
            }
            else{
                assert(tarr1[y][x] == FIRE);
            }
        }
    }
    assert(tarr1[midy-2][midx-2] == TREE);
    assert(tarr1[midy+2][midx+2] == TREE);
    assert(tarr1[0][0] == TREE);
    reassign(tarr1, tmp);
    /* Reassign */
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            assert(tarr1[y][x] == EMPTY);
        }
    }
    for(y=0; y<TALL; y++){
        tarr1[y][0] = TREE;
    }
    tarr1[0][0] = FIRE;
    tarr1[TALL-1][midx] = FIRE;
    fire_spread(tarr1);
    /* Fire spread */
    assert(tarr1[0][0] == EMPTY);
    assert(tarr1[1][0] == FIRE);
    assert(tarr1[TALL-1][WIDE-1] == EMPTY);
    assert(tarr1[TALL-1][WIDE-2] == EMPTY);
    assert(tarr1[0][1] == EMPTY);
    assert(tarr1[midy][0] == TREE);
    assert(tarr1[TALL-1][0] == TREE);
    assert(tarr1[TALL-1][midx] == EMPTY);
    assert(tarr1[TALL-1][midx+1] == EMPTY);
    assert(tarr1[TALL-1][midx-1] == EMPTY);
    assert(tarr1[TALL-2][midx] == EMPTY);
    /* Birth */
    for(i=0; i<GENERATIONS; i++){
        birth_lightning(tarr2);
        for(y=0; y<TALL; y++){
            for(x=0; x<WIDE; x++){
                if(tarr2[y][x] == TREE){
                    tree_cnt++;
                }
            }
        }
        reassign(tarr2, tmp);
    }
    tree_cnt = tree_cnt/(double)GENERATIONS;
    exact = TALL*WIDE/(double)BIRTHRATE;
    assert(tree_cnt > exact-EMARG && tree_cnt < exact+EMARG);
    /* Lightning */
    for(i=0; i<GENERATIONS; i++){
        reassign(tarr3, tmp2);
        birth_lightning(tarr3);
        for(y=0; y<TALL; y++){
            for(x=0; x<WIDE; x++){
                if(tarr3[y][x]==FIRE){
                    fire_cnt++;
                }
            }
        }
    }
    fire_cnt = fire_cnt/(double)GENERATIONS;
    exact = TALL*WIDE/(double)LIGHTNING;
    assert(fire_cnt >= exact-EMARG && fire_cnt <= exact+EMARG);
    /* calc_char */
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            assert(calc_char(tmp[y][x]) == EMPTYSYMBOL);
            assert(calc_char(tmp2[y][x]) == TREESYMBOL);
            assert(calc_char(tmp3[y][x]) == FIRESYMBOL);
            assert(tarr1[y][x] != WRONGSYMBOL);
            assert(tarr2[y][x] != WRONGSYMBOL);
            assert(tarr3[y][x] != WRONGSYMBOL);
        }
    }
    assert(calc_char(INCORRECT) == WRONGSYMBOL);
    assert(calc_char(FIRE) == FIRESYMBOL);
    assert(calc_char(TREE) == TREESYMBOL);
    assert(calc_char(EMPTY) == EMPTYSYMBOL);
}
