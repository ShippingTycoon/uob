#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

enum bool {false, true};
typedef enum bool bool;

#define WIDE 150
#define TALL 90
#define XYSTART 1
#define RNUMSTART 1
#define FLINESIZE 10
#define XY 2
#define LIVE 1
#define DEATH 0
#define LIVEC1 '@'
#define LIVEC2 '+'
#define DEATHC ' '
#define X 0
#define Y 1
#define NUMCOORDINATES 5
#define MAXRULES 3
#define MAXNUMS 10
#define NORULE 12
#define RBIRTH 9
#define RSURVIVAL 10
#define RDEATH 11
#define NOPLAYER 3
#define PLAYER1 1
#define PLAYER2 2
#define MAXLINES 100
#define NUMPLAYERS 2
#define NUMGAMES 50
#define GENERATIONS 1
#define TOCHECK 3
#define WAITTIME 0.1

struct game{
    int state;
    int player;
};

void init_board(struct game board[TALL][WIDE]);

void setup_game(char* infile1, char* infile2, 
struct game board[TALL][WIDE]);

/* Open file and take info into string array */
int load(const char *infile, 
char buffer[MAXLINES][FLINESIZE]);

/* Parse strings into int coordinates */
void to_xy(char buffer[MAXLINES][FLINESIZE], 
int xy[MAXLINES][XY], int len);

/* Fills in board with start coordinates from file */
bool setup_board(int xy[MAXLINES][XY], 
struct game board[TALL][WIDE], int len, int player);

void play_game(struct game board[TALL][WIDE]);

/* Iterate through array and change values accordingly */
void life(struct game board[TALL][WIDE]);

void check_8(int x, int y, struct game board[TALL][WIDE], 
int cnt[NUMPLAYERS]);

int wrapx(int x);

int wrapy(int y);

int update_player(int state, int cnt[NUMPLAYERS]);

/* Check individual cells agains rules */
int check_cell(int cnt[NUMPLAYERS], int cell);

void reassign(struct game board[TALL][WIDE], 
struct game tmp[TALL][WIDE]);

/* Assign all vals in tmp array to 0 */
void zero_tmp(struct game tmp[TALL][WIDE]);

/* Convert int value of cell into printable char */
char tochar(struct game pos);

void test(void);

int main(int argc, char **argv)
{
    int i;
    struct game board[TALL][WIDE];
    srand(time(NULL));
    if(argc == 3){
        char* infile1 = argv[1];
        char* infile2 = argv[2];
        test();
        for(i=0; i<1; i++){
            setup_game(infile1, infile2, board);
            play_game(board);
            /* printf("Game played\n"); */
        }
    }
    else{
        printf("Usage: lifewars file1.lif file2.lif\n");
    }
    return 0;
}

void init_board(struct game board[TALL][WIDE])
{
    int y, x;
    /* printf("init_board\n"); */
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            board[y][x].state = DEATH;
            board[y][x].player = NOPLAYER;
        }
    }
}

void setup_game(char* infile1, char* infile2, 
struct game board[TALL][WIDE])
{
    int len1, len2;
    char buffer[MAXLINES][FLINESIZE];
    int xyp1[MAXLINES][XY] = {0};
    int xyp2[MAXLINES][XY] = {0};
    bool p1 = true;
    bool p2 = true;
    /* printf("setup_game\n"); */
    init_board(board);
    len1 = load(infile1, buffer);
    to_xy(buffer, xyp1, len1);
    len2 = load(infile2, buffer);
    to_xy(buffer, xyp2, len2);
    do{
        init_board(board);
        p1 = setup_board(xyp1, board, len1, PLAYER1);
        p2 = setup_board(xyp2, board, len2, PLAYER2);
    }while(p1 == false || p2 == false);
}

int load(const char* infile, char buffer[MAXLINES][FLINESIZE])
{
    FILE *file;
    int i, j, c, len = 0;
    /*printf("load\n"); */
    if((file = fopen(infile, "r")) == NULL){
        fprintf(stderr, "Couldn't load file %s\n", infile);
        exit(EXIT_FAILURE);
    }
    /* Skip first line of file */
    do{
        c = fgetc(file);
    }while(c != EOF && c != '\n');
    i=0;
    do{
        j = 0;
        do{
            c = (buffer[i][j++] = fgetc(file));
        }while(c != EOF && c != '\n');
        len++;
        buffer[i++][j] = '\0';
    }while(c != EOF);
    buffer[i-1][j-1] = '\0';
    fclose(file);
    return len;
}

void to_xy(char buffer[MAXLINES][FLINESIZE], 
int xy[MAXLINES][XY], int len)
{
    int j;
    int i;
    char* token;
    /*https://www.educative.io/edpresso/splitting-a-string-using-strtok-in-c */
    for(i=0; i<len; i++){
        j=0;
        token = strtok(buffer[i], " ");
        while(token != NULL){
            xy[i][j] = atoi(token);
            token = strtok(NULL, " ");
            j++;
        }
    }
}

bool setup_board(int xy[MAXLINES][XY], 
struct game board[TALL][WIDE], int len, int player)
{
    int i; 
    int posx, posy, rposx, rposy;
    rposx = rand()%WIDE;
    rposy = rand()%TALL;
    /* printf("setup_board\n"); */
    for(i=0; i<len; i++){
        posx = rposx + xy[i][X];
        posy = rposy + xy[i][Y];
        if(posx<0 || posx>=WIDE){
            posx = wrapx(posx);
        }
        if(posy<0 || posy>=TALL){
            posy = wrapy(posy);
        }
        if(board[posy][posx].state == LIVE){
            return false;
        }
        board[posy][posx].state = LIVE;
        board[posy][posx].player = player;
        printf("%d, %d\n", posx, posy);
    }
    return true;
}

void play_game(struct game board[TALL][WIDE])
{
    int i, j, k;
    /* printf("play_game\n"); */
    for(i=0; i<GENERATIONS; i++){
        life(board);
        for(j=0; j<TALL; j++){
            for(k=0; k<WIDE; k++){
                printf("%c", tochar(board[j][k]));
            }
            printf("\n");
        }
    }
}

void life(struct game board[TALL][WIDE])
{
    int i, j;
    int cnt[NUMPLAYERS] = {0};
    struct game tmp[TALL][WIDE];
    /* printf("life"); */
    init_board(tmp);
    /* Iterate through the current board */
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            cnt[0]=0;
            cnt[1]=0;
            /* Check 8 cells around */
            check_8(i, j, board, cnt);
            tmp[i][j].state = check_cell(cnt,
            board[i][j].state);
            tmp[i][j].player = update_player(
                tmp[i][j].state, cnt);
            if(tmp[i][j].state == LIVE){
                printf("%d, %d\n", i, j);
            }
        }
    }
    reassign(board, tmp);
}

void check_8(int i, int j, struct game board[TALL][WIDE], 
int cnt[NUMPLAYERS])
{
    int tmpy, tmpx, x, y;
    for(y=i-1; y<=i+1; y++){
        for(x=j-1; x<=j+1; x++){
            tmpx = x;
            tmpy = y;
            if(y<0 || y>=TALL){
                tmpy = wrapy(y);
            }
            else if(x<0 || x>=WIDE){
                tmpx = wrapx(x);
            }
            else if(y==i && x==j){
                /* Skip */
            }
            else if(board[tmpy][tmpx].state == LIVE &&
            board[tmpy][tmpx].player == PLAYER1){
                cnt[0]++;
            }
            else if(board[tmpy][tmpx].state == LIVE &&
            board[tmpy][tmpx].player == PLAYER2){
                cnt[1]++;
            }
        }
    }
}

int wrapx(int x)
{
    /* printf("wrapx\n"); */
    if(x<0){
        return x+WIDE;
    }
    else{
        return x-WIDE;
    }
}

int wrapy(int y)
{
    /* printf("wrapy\n"); */
    if(y<0){
        return y+TALL;
    }
    else{
        return y-TALL;
    }
}

int update_player(int state, int cnt[NUMPLAYERS])
{
    switch(state){
        case LIVE:
            if(cnt[0]>cnt[1]){
                return PLAYER1;
            }
            else if(cnt[0] == cnt[1]){
                return NOPLAYER;
            }
            else{
                return PLAYER2;
            }
        case DEATH:
            return NOPLAYER;
        default:
            return NOPLAYER;
    }
}

void reassign(struct game board[TALL][WIDE], 
struct game tmp[TALL][WIDE])
{
    int i, j;
    /* printf("reassign\n"); */
    for(i=0; i<TALL; i++){
        for(j=0; j<WIDE; j++){
            board[i][j].state = tmp[i][j].state;
            board[i][j].player = tmp[i][j].player;
        }
    }
}

int check_cell(int cnt[NUMPLAYERS], int cell)
{
    int count = cnt[0]+cnt[1];
    switch(cell){
        case LIVE:
            if(count==3 || count == 2){
                return LIVE;
            }
            else{
                return DEATH;
            }
        case DEATH:
            if(count ==3){
                return LIVE;
            }
            else{
                return DEATH;
            }
    }
    return 3;
}

char tochar(struct game pos)
{
    switch (pos.state){
    case LIVE:
        if(pos.player == PLAYER1){
            return LIVEC1;
        }
        else{
            return LIVEC2;
        }
        break;
    default:
        return DEATH;
        break;
    }
}

void test(void)
{
    FILE* file;
    char tbuff[MAXLINES][FLINESIZE];
    struct game tboard[TALL][WIDE];
    struct game temptest[TALL][WIDE];
    int xyt1[MAXLINES][XY];
    int y, x, i;
    int len;
    int cnt[NUMPLAYERS] = {0};
    int midx = WIDE/2;
    int midy = TALL/2;
    int tcell;
    int tstate;
    double cnt1s;
    init_board(tboard);
    /* Initialise board */
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            assert(tboard[y][x].state == DEATH);
            assert(tboard[y][x].player == NOPLAYER);
        }
    }
    /* File Opens */
    if((file = fopen("file1.lif", "r")) == NULL){
        exit(EXIT_FAILURE);
    }
    /* Get number of coordinates */
    len = load("file1.lif", tbuff);
    assert(len == NUMCOORDINATES);
    to_xy(tbuff, xyt1, len);
    /* Convert strings to integer coordinates */
    assert(xyt1[0][0] == 0);
    assert(xyt1[0][1] == -1);
    assert(xyt1[4][0] == 1);
    /* Setting up board with one player should always work */
    assert(setup_board(xyt1, tboard, len, PLAYER1) == true);
    init_board(tboard);
    for(y=midy-1; y<=midy+1; y++){
        for(x=midx-1; x<=midx+1; x++){
            if(y==midy && x==midx){
                /* Skip */
            }
            tboard[y][x].state = LIVE;
            tboard[y][x].player = PLAYER1;
        }
    }
    /* Check 8 */
    check_8(midy, midx, tboard, cnt);
    assert(cnt[0] == 8);
    assert(cnt[1] == 0);
    init_board(tboard);
    for(y=midy-1; y<=midy+1; y++){
        for(x=midx-1; x<=midx+1; x++){
            if(y==midy && x==midx){
                /* Skip */
            }
            tboard[y][x].state = LIVE;
            tboard[y][x].player = PLAYER2;
        }
    }
    check_8(midy, midx, tboard, cnt);
    assert(cnt[0] == 8);
    assert(cnt[1] == 8);
    for(i=0; i<NUMPLAYERS; i++){
        cnt[i] = 0;
    }
    check_8(0, 0, tboard, cnt);
    for(i=0; i<NUMPLAYERS; i++){
        assert(cnt[i] == 0);
    }
    /* Check cell */
    cnt[0] = 2;
    cnt[1] = 1;
    tcell = DEATH;
    tcell = check_cell(cnt, tcell);
    assert(tcell == LIVE);
    cnt[0] = 2;
    cnt[1] = 0;
    tcell = check_cell(cnt, tcell);
    assert(tcell == LIVE);
    cnt[0] = 3;
    cnt[1] = 4;
    tcell = check_cell(cnt, tcell);
    assert(tcell == DEATH);
    /* Update player */
    tstate = LIVE;
    cnt[0] = 4;
    cnt[1] = 3;
    assert(update_player(tstate, cnt) == PLAYER1);
    cnt[0] = 3;
    cnt[1] = 4;
    assert(update_player(tstate, cnt) == PLAYER2);
    cnt[0] = 2;
    cnt[1] = 2;
    cnt1s = 0.0;
    tstate = DEATH;
    assert(update_player(tstate, cnt) == NOPLAYER);
    /* Reassign */
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            temptest[y][x].player = NOPLAYER;
            temptest[y][x].state = DEATH;
        }
    }
    reassign(tboard, temptest);
    for(y=0; y<TALL; y++){
        for(x=0; x<WIDE; x++){
            assert(tboard[y][x].player == NOPLAYER);
            assert(tboard[y][x].state == DEATH);
        }
    }
}
