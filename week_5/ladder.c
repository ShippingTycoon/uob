#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORDS 2892
#define WORDS34 320125
#define MAXLEN 50
#define WORDLEN 4
#define NOT4 3
#define EDITDIST 4
#define ONEAWAY 1

enum bool {false, true};
typedef enum bool bool;

struct letter {
    char l;
    bool changed;
};

void test(void);

void load(char dic[MAXWORDS][MAXLEN]);
int check_dic(char* word, char dic[MAXWORDS][MAXLEN], char* target);
void get_word(char new_word[WORDLEN], char*dic_item);
bool one_closer(char* word, char dic_word[WORDLEN], char* target);
int update_word(char word[WORDLEN], char new_word[WORDLEN]);
void printword(char word[WORDLEN]);

int edit_distance(char* s, char* t);

int main(int argc, char** argv)
{
    char dic[MAXWORDS][MAXLEN];
    char new_word[WORDLEN];
    int i, pos;
    if(argc == 3){
        char* start = argv[1];
        char* target = argv[2];
        if(edit_distance(start, target) != EDITDIST){
            fprintf(stderr, "Incompatible words\n");
            exit(EXIT_FAILURE);
        }
        load(dic);
        printf("%d ", update_word(start, start));
        printword(start);
        for(i=0; i<EDITDIST; i++){
            pos = check_dic(start, dic, target);
            get_word(new_word, dic[pos]);
            printf("%d ", update_word(start, new_word));
            printword(start);
        }
    }
    else{
        fprintf(stderr, "Usage: ./ladder word word\n");
        exit(EXIT_FAILURE);
    }
}

int edit_distance(char* s, char* t)
{
    int i, dist = 0;
    for(i=0; i<WORDLEN; i++){
        if(s[i] != t[i]){
            dist++;
        }
    }
    return dist;
}

void load(char dic[MAXWORDS][MAXLEN])
{
    FILE *file;
    int i, j, c, cnt = 0;
    /*printf("load\n"); */
    if((file = fopen("34words.txt", "r")) == NULL){
        fprintf(stderr, "Couldn't open file\n");
        exit(EXIT_FAILURE);
    }
    i=0;
    do{
        j = 0;
        do{
            c = (dic[i][j++] = fgetc(file));
        }while(c != EOF && c != '\n' );
        dic[i++][j-1] = '\0';
        cnt++;
    }while(c != EOF);
    fclose(file);
}

int check_dic(char* word, char dic[MAXWORDS][MAXLEN], char* target)
{
    int i, len;
    for(i=0; i<MAXWORDS; i++){
        len = strlen(dic[i]);
        if(len == WORDLEN && one_closer(word, dic[i], target)){
            return i;
        }
    }
    fprintf(stderr, "Couldn't find a match\n");
    exit(EXIT_FAILURE);
}

void get_word(char new_word[WORDLEN], char*dic_item)
{
    int i;
    for(i=0; i<WORDLEN; i++){
        new_word[i] = dic_item[i];
    }
}

bool one_closer(char* word, char dic_word[WORDLEN], char* target)
{
    int from_word, to_target, word_target;
    from_word = edit_distance(word, dic_word);
    to_target = edit_distance(dic_word, target);
    word_target = edit_distance(word, target);
    if(from_word == ONEAWAY && to_target == word_target-1){
        return true;
    }
    else{
        return false;
    }
}

int update_word(char word[WORDLEN], char new_word[WORDLEN])
{
    int i;
    for(i=0; i<WORDLEN; i++){
        if(word[i] != new_word[i]){
            word[i] = new_word[i];
            return i+1;
        }
    }
    return 0;
}

void printword(char word[WORDLEN])
{
    int i;
    for(i=0; i<WORDLEN; i++){
        printf("%c", word[i]);
    }
    printf("\n");
}

void test(void)
{
    char tdic[MAXWORDS][MAXLEN];
    char tword[WORDLEN];
    char* tester = "poke";
    int i;
    assert(edit_distance("wild", "tame") == EDITDIST);
    assert(edit_distance("poke", "mall") == EDITDIST);
    assert(edit_distance("cube", "tons") == EDITDIST);
    assert(edit_distance("hello", "hello") == 0);
    load(tdic);
    assert(tdic[MAXWORDS-2][0] == 't');
    assert(tdic[0][0] == 'w');
    assert(tdic[0][3] == 'k');
    assert(one_closer("cold", "cord", "warm") == true);
    assert(one_closer("cord", "card", "warm") == true);
    get_word(tester, "pole");
    assert(strcmp(tester, "pole") == 0);
    for(i=0; i<WORDLEN; i++){
        tword[i] = tester[i];
    }
    update_word(tword, "pole");
    assert(tword[2] == 'l');
}
