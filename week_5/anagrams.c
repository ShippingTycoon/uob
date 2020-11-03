#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

#define MAXWORDS 2892
#define MAXLEN 15

enum bool {false, true};
typedef enum bool bool;

void test(void);
void load(char buffer[MAXWORDS][MAXLEN]);
void check_dic(char dic[MAXWORDS][MAXLEN], char* word);
bool compare(char* word, char* dic_item, int len);

int main(int argc, char** argv)
{
    char dic[MAXWORDS][MAXLEN];
    test();
    if(argc == 2){
        char* word = argv[1];
        load(dic);
        check_dic(dic, word);
    }
    else{
        fprintf(stderr, "Usage: ./anagrams filename.txt");
    }
    return 0;
}

void load(char dic[MAXWORDS][MAXLEN])
{
    FILE *file;
    int i, j, c;
    /*printf("load\n"); */
    if((file = fopen("34words.txt", "r")) == NULL){
        fprintf(stderr, "Couldn't load file\n");
        exit(EXIT_FAILURE);
    }
    i=0;
    do{
        j = 0;
        do{
            c = (dic[i][j++] = fgetc(file));
        }while(c != EOF && c != '\n' );
        dic[i++][j-1] = '\0';
    }while(c != EOF);
    fclose(file);
}

void check_dic(char dic[MAXWORDS][MAXLEN], char* word)
{
    int i;
    bool in_both;
    int len = strlen(word);
    for(i=0; i<MAXWORDS-1; i++){
        in_both = false;
        if(len == (int)strlen(dic[i])){
            /* Do further tests */
            if(compare(word, dic[i], len)==true &&
            compare(dic[i], word, len) ==true){
                in_both = true;
            }
        }
        if(in_both==true){
                printf("%s\n", dic[i]);
        }
    }
}

bool compare(char* word, char* dic_item, int len)
{
    int i, j;
    bool here;
    for(i=0; i<len; i++){
        here = false;
        for(j=0; j<len; j++){
            if(word[i] == dic_item[j]){
                here = true;
            }
        }
        if(here == false){
            return false;
        }
    }
    return true;
}

void test(void)
{
    char tdic[MAXWORDS][MAXLEN];
    int len;
    load(tdic);
    assert(tdic[0][0] == 'w');
    assert(tdic[MAXWORDS-2][0] == 't');
    assert(tdic[MAXWORDS-2][3] == 's');
    assert(tdic[MAXWORDS-2][4] == '\0');
    assert(tdic[0][4] == '\0');
    len = strlen(tdic[MAXWORDS-2]);
    assert(len == 4);
    assert(compare("vidad", "david", 5) == true);
    assert(compare("meoinher", "hermione", 8) == true);
}
