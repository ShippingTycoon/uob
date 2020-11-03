#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define GENERATIONS 1000
#define BIRTHRATE 250
#define LIGHTNING 500
#define EMARG 0.7
#define TALL 30
#define WIDE 80
#define EMPTY 0
#define TREE 1
#define FIRE 2
#define FIRESYMBOL '*'
#define TREESYMBOL '@'
#define EMPTYSYMBOL ' '
#define WRONGSYMBOL '?'

void test(void);
void fire_spread(int grid[TALL][WIDE]);
void reassign(int grid[TALL][WIDE], int tmp[TALL][WIDE]);
void birth_lightning(int grid[TALL][WIDE]);
void lightning(int grid[TALL][WIDE]);
char calc_char(int a);

int main(void)
{
    int grid[TALL][WIDE] = {0};
    int i, j, k;
    srand(time(NULL));
    test();
    for(i=0; i<GENERATIONS; i++){
        fire_spread(grid);
        birth_lightning(grid);
        for(j=0; j<TALL; j++){
            for(k=0; k<WIDE; k++){
                printf("%c", calc_char(grid[j][k]));
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}

void birth_lightning(int grid[TALL][WIDE])
{
    int i, j;
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            if(grid[i][j] == EMPTY){
                if(rand()%BIRTHRATE == 0){
                    grid[i][j] = TREE;
                }
            }
            else if(grid[i][j] == TREE){
                if(rand()%LIGHTNING == 0){
                    grid[i][j] = FIRE;
                }
            }
        }
    }
}

void fire_spread(int grid[TALL][WIDE])
{
    int i, j, k, l;
    int tmp[TALL][WIDE];
    /* Iterate through array */
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            tmp[i][j] = grid[i][j];
            /* Check each cells 8 neighbours */
            for(k=i-1; k<=i+1; k++){
                for(l=j-1; l<=j+1; l++){
                    if(k<0 || l<0 || k>=TALL || l>=WIDE){
                        /* Skip */
                    }
                    else if(grid[k][l] == FIRE && 
                    grid[i][j] == TREE){
                        tmp[i][j] = FIRE;
                    }
                }
            }
        }
    }
    reassign(grid, tmp);
}

void reassign(int grid[TALL][WIDE], int tmp[TALL][WIDE])
{
    int i, j;
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            /* Fire goes out */
            if(grid[i][j] == FIRE){
                grid[i][j] = EMPTY;
            }
            else{
                grid[i][j] = tmp[i][j];
            }
        }
    }
}

char calc_char(int a)
{
    if(a==EMPTY){
        return EMPTYSYMBOL;
    }
    else if(a==TREE){
        return TREESYMBOL;
    }
    else if(a==FIRE){
        return FIRESYMBOL;
    }
    else{
        return WRONGSYMBOL;
    }
}

void test(void)
{
    int i, j, k;    
    int tarr1[TALL][WIDE] = {0};
    int tarr2[TALL][WIDE] = {0};
    int tmp[TALL][WIDE] = {0};
    int tmp2[TALL][WIDE];
    int tmp3[TALL][WIDE];
    int tarr3[TALL][WIDE];
    double tree_cnt = 0.0;
    double fire_cnt = 0.0;
    double exact;
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            tmp2[i][j] = TREE;
        }
    }
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            assert(tmp2[i][j] == TREE);
        }
    }
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            tmp3[i][j] = FIRE;
        }
    }
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            tarr1[i][j] = TREE;
        }
    }
    tarr1[TALL/2][WIDE/2] = FIRE;
    fire_spread(tarr1);
    /* Fire spread */
    for(i=(TALL/2)-1; i<=(TALL/2)+1; i++){
        for(j=(WIDE/2)-1; j<=(WIDE/2)+1; j++){
            if(i==TALL/2 && j==WIDE/2){
                assert(tarr1[i][j] == EMPTY);
            }
            else{
                assert(tarr1[i][j] == FIRE);
            }
        }
    }
    reassign(tarr1, tmp);
    /* Reassign */
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            assert(tarr1[i][j] == EMPTY);
        }
    }
    for(i=0; i<TALL; i++){
        tarr1[i][0] = TREE;
    }
    tarr1[0][0] = FIRE;
    tarr1[TALL-1][5] = FIRE;
    fire_spread(tarr1);
    /* Fire spread */
    assert(tarr1[0][0] == EMPTY);
    assert(tarr1[1][0] == FIRE);
    assert(tarr1[TALL-1][5] == EMPTY);
    assert(tarr1[TALL-1][4] == EMPTY);
    assert(tarr1[0][1] == EMPTY);
    assert(tarr1[10][0] == TREE);
    assert(tarr1[TALL-1][0] == TREE);
    /* Birth */
    for(k=0; k<GENERATIONS; k++){
        birth_lightning(tarr2);
        for(i=0; i<TALL; i++){
            for(j=0; j<WIDE; j++){
                if(tarr2[i][j] == TREE){
                    tree_cnt++;
                }
            }
        }
        reassign(tarr2, tmp);
    }
    tree_cnt = tree_cnt/(double)GENERATIONS;
    exact = TALL*WIDE/(double)BIRTHRATE;
    assert(tree_cnt>exact-EMARG && tree_cnt < exact+EMARG);
    /* Lightning */
    for(k=0; k<GENERATIONS; k++){
        reassign(tarr3, tmp2);
        birth_lightning(tarr3);
        for(i=0; i<TALL; i++){
            for(j=0; j<WIDE; j++){
                if(tarr3[i][j] == FIRE){
                    fire_cnt++;
                }
            }
        }
    }
    fire_cnt = fire_cnt/(double)GENERATIONS;
    exact = TALL*WIDE/(double)LIGHTNING;
    assert(fire_cnt >=exact-EMARG && fire_cnt <=exact+EMARG);
    /* calc_char */
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            assert(calc_char(tmp[i][j]) == ' ');
            assert(calc_char(tmp2[i][j]) == '@');
            assert(calc_char(tmp3[i][j]) == '*');
        }
    }
}
