#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "neillsimplescreen.h"
#include <assert.h>

typedef enum bool {false, true} bool;

#define HEIGHT 10
#define WIDTH 10

#define START_X 0
#define START_Y 1

#define W '#'
#define H ' '
#define X '*'
#define P '.'
#define T 'T' /* Stops you going back to cells already visited */

/* If having trouble, fill with print statements that tell
 you the current value of x and y */

void print_maze(char maze[HEIGHT][WIDTH]);
bool explore(int x, int y, char mz[HEIGHT][WIDTH]);

int main(void)
{
    char mz[HEIGHT][WIDTH]={{'#','#','#','#','#','#','#','#','#','#'},
                            {' ',' ','#',' ',' ',' ',' ',' ',' ','#'},
                            {'#',' ','#',' ','#',' ','#','#',' ','#'},
                            {'#',' ','#',' ','#','#','#','#',' ','#'},
                            {'#',' ','#',' ',' ',' ',' ','#',' ','#'},
                            {'#',' ','#',' ','#','#','#','#',' ','#'},
                            {'#',' ','#',' ',' ',' ',' ','#',' ','#'},
                            {'#',' ','#','#','#','#',' ','#',' ','#'},
                            {'#',' ',' ',' ',' ',' ',' ','#',' ','*'},
                            {'#','#','#','#','#','#','#','#','#','#'}};
    
    print_maze(mz);
    assert(mz[START_Y][START_X] = H);
    if(explore(START_X, START_Y, mz)){
        printf("\n");
        assert(mz[START_Y][START_X] = H);
        print_maze(mz);
    }
    else{
        print_maze(mz);
        printf("No valid route ?\n");
    }
    return 0;
}

bool explore(int x, int y, char mz[HEIGHT][WIDTH])
{
    /* If it's marked with a cross we have escaped*/
    if (mz[y][x] == X){
        return true;
    } 

    mz[y][x] = T;

    /* If we can move in this direction it means we can escape from here */
    if (mz[y+1][x] == X || (y+1 <HEIGHT && mz[y+1][x] == H)){
        if(explore(x, y+1, mz) == true){
            return true;
        }
    }
    
    if(mz[y][x+1] == X || (x+1<WIDTH && mz[y][x+1] == H)){
        if(explore(x+1, y, mz)==true){
            return true;
        }
    } 
    if(mz[y][x-1] == X || (x-1>=0 && mz[y][x-1] == H)){
        if(explore(x-1, y, mz)==true){
            return true;
        }
    } 
    if(mz[y-1][x] == X || (y-1>=0 && mz[y-1][x] == H)){
        if(explore(x, y-1, mz)==true){
            return true;
        }
    } 

    return false; /* Failed to find route */
}

void print_maze(char maze[HEIGHT][WIDTH])
{
    int i, j;
    char c;
    for(j=0; j<HEIGHT; j++){
        for(i=0; i<WIDTH; i++){
            c=maze[j][i];
            switch(c){
                case H:
                case X:
                case W:
                    /*neillfgcol(green);*/
                    break;
                case T:
                    c='.';
                    break;
                default:
                    /*neillfgcol(red);*/
                    break;
            }
            printf("%c", c);
        }
        printf("\n");
    }
    printf("\n");
}
