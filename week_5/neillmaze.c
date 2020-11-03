#include <stdio.h>
#include <string.h>
typedef enum bool {false, true} bool;
#include "neillsimplescreen.h"

#define HEIGHT 10
#define WIDTH 10

#define START_X 1
#define START_Y 0

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
    char maze[HEIGHT][WIDTH] = {{W,H,W,W,W,W,W,W,W,W};
    /* ... more writing out maze */

    print_maze(maze);
    if(explore(START_X, START_Y, maze)){
        printf("\n");
        maze[START_Y][START_X] = H;
        print_maze(maze);
    }
    else{
        printf("No valid route ?\n");
    }
    return 0;
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
                    neillfgcol(green);
                    break;
                case T:
                    c=' ';
                    break;
                default:
                    neillfgcol(red);
            }
            printf("%c", c);
        }
        printf("\n");
    }
    printf("\n");
}