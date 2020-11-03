#include <stdio.h>

enum bool {false, true};
typedef enum bool bool;

enum direction {right, left, down, up};
typedef enum direction direction;

#define TALL 5
#define WIDE 5
#define STARTX 0
#define STARTY 0
#define STARTPOS 1
#define ENDPOS 25
#define EMPTY 0

void path(int y, int x, int board[TALL][WIDE], int pos);
void print_path(int board[TALL][WIDE]);
void remove_higher(int board[TALL][WIDE], int pos);

int main(void)
{
    int board[TALL][WIDE] = {{0}};
    int pos = STARTPOS;
    path(STARTY, STARTX, board, pos);
}

void path(int y, int x, int board[TALL][WIDE], int pos)
{
    board[y][x] = pos;
    remove_higher(board, pos);

    if(pos == ENDPOS){
        print_path(board);
    }

    /* Move right */
    if(x+1 < WIDE && board[y][x+1] == EMPTY){
        path(y, x+1, board, pos+1);
        remove_higher(board, pos);
    }
    /* Move left */
    if(x-1 >=0 && board[y][x-1] == EMPTY){
        path(y, x-1, board, pos+1);
        remove_higher(board, pos);
    }
    /* Move up */
    if(y+1 <TALL && board[y+1][x] == EMPTY){
        path(y+1, x, board, pos+1);
        remove_higher(board, pos);
    }
    /* Move down */
    if(y-1>=0 && board[y-1][x] == EMPTY){
        path(y-1, x, board, pos+1);
        remove_higher(board, pos);
    }
}

void remove_higher(int board[TALL][WIDE], int pos)
{
    int i, j;
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            if(board[i][j] > pos){
                board[i][j] = 0;
            }
        }
    }
}

void print_path(int board[TALL][WIDE])
{
    int i, j;
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            printf("%d", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
