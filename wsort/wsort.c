#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_WORD_LENGTH 101

static char **wordList;

static int wordListLength = 0;

static int insertWord(char *word){
    if(wordList == NULL){
        wordList = (char**)calloc(1, sizeof(char**));
        if(wordList == NULL){
            perror("calloc");
            exit(EXIT_FAILURE);
        }
        wordList[wordListLength] = malloc(MAX_WORD_LENGTH * sizeof(char));
        if(wordList[wordListLength] == NULL){
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strcpy(wordList[wordListLength++], word);
    }else{
        wordList = (char**)realloc(wordList, (wordListLength+1)*sizeof(char**));
        if(wordList == NULL){
            perror("calloc");
            exit(EXIT_FAILURE);
        }
        wordList[wordListLength] = malloc(MAX_WORD_LENGTH * sizeof(char));
        if(wordList[wordListLength] == NULL){
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strcpy(wordList[wordListLength++], word);
    }
    return 1;
}
static int cmp(const void *worda , const void *wordb){
    //from qsort manu

    return strcmp(*(const char** ) worda, *(const char** ) wordb);
}


static void export(){
    for(int i = 0; i < wordListLength; i++){
        if(printf("%s", wordList[i]) < 0 ){
            perror("printf");
            exit(EXIT_FAILURE);
        }
    }
    if(fflush(stdout) == EOF){
        perror("fflush stdout");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]){
    char buff[MAX_WORD_LENGTH];
    int finished = 0;
    while(finished == 0){
        if(fgets(buff, MAX_WORD_LENGTH, stdin) != NULL){
            if(buff[0] == EOF){
                finished = 1 ;
            } else if (buff[MAX_WORD_LENGTH-1] == '\n'){
                perror("Word too long");
                if (fflush(stdin) == EOF){
                    fprintf(stderr, "Wort zu lang...ignoriere\n");
                    exit(EXIT_FAILURE);
                }
            } else if (buff[0] == '\n') {
                // Leere Zeilen werden ohne Fehlermeldenung ignoriert
            }
            else{
                buff[MAX_WORD_LENGTH-1] = '\0';
                insertWord(buff);
            }
        } else {
            finished = 1;
        }
    }
    qsort(wordList, wordListLength, sizeof(char*), cmp);

    //print out sorted wordList
    export();

    //free wordlist
    for(int i = 0; i < wordListLe