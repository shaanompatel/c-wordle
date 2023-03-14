#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 12971
#define MAX_LEN 7
char valid[MAX_LINES][MAX_LEN];

void playGame(char *ans);
bool validateWord(char *guess);
char* genAnswer();
int genRandom();
void printColor(char *guess, char *ans);
bool contains(char *ans, char guess);
int numAppearance(char a, char *ans);

int main(){
    char* ANSWER;
    ANSWER = genAnswer();
    printf("%s\n", ANSWER);
    playGame(ANSWER);
    return 0;
}

void playGame(char *ans){
    bool won = false;
    int tries = 0;
    char guess[7];
    while (!won && tries <= 5){
        tries++;
        do {
            scanf("%s", guess);
        } while (!validateWord(guess));

        printf("\033[A");
        printf("\33[2K\r");
        fflush(stdout);
        printColor(guess, ans);

        if (strcmp(guess, ans) == 0){
            won = true;
        }
    }
    if (won){
        printf("You won in %d tr%s.\n", tries, (tries!=1) ? "ies" : "y");
    } else {
        printf("You ran out of tries. The word was %s\n.", ans);
    }
}

bool validateWord(char *guess){
    int i;
    for(i=0;i<(sizeof valid / sizeof valid[0]);i++){
        if (strcmp(valid[i], guess) == 0){
            return true;
        }
    }
    
    printf("\033[A");
    printf("\33[2K\r");
    fflush(stdout);
    return false;
}

char* genAnswer(){
    FILE *fpointer = fopen("valid.txt", "r");
    int line = 0;
    while(line <= MAX_LINES && !feof(fpointer)){
        if (fgets(valid[line], MAX_LEN, fpointer)!=NULL){
            valid[line][5] = '\0';
            line++;
        }
    }
    fclose(fpointer);
    return(valid[genRandom()]);
}

int genRandom(){
    srand(time(NULL)); 
    int num = (rand() % (MAX_LINES - 0 + 1));
    return num;
}

void printColor(char *guess, char *ans){
    int index = 0;
    int greenCount = 0;
    int yellowCount = 0;
    char checked[6];
    char colors[6][25];

    int i;
    for(i=0;i<5;i++){
        if (guess[i] == ans[i]){
            strcpy(colors[i], "\033[0;32m");
            checked[index] = guess[i];
            index++;
        }
    }
    for(i=0;i<5;i++){
        if (contains(ans, guess[i])){
            if (numAppearance(guess[i], ans) > numAppearance(guess[i], checked)){
                if (strcmp(colors[i], "\033[0;32m") != 0){
                    strcpy(colors[i], "\033[0;33m");
                    checked[index] = guess[i];
                    index++;
                }
            }
        }
    }
    for(i=0;i<5;i++){
        if (strcmp(colors[i], "\033[0;32m") != 0 && strcmp(colors[i], "\033[0;33m") != 0){
            strcpy(colors[i], "\033[0;31m");
        }
    }
    for(i=0; i<5;i++){
        printf("%s%c", colors[i], guess[i]);
    }
    printf("\033[0m\n");
}

bool contains(char *ans, char guess){
    int i;
    for(i=0;i<5;i++){
        if (ans[i] == guess){
            return true;
        }
    }
    return false;
}

int numAppearance(char a, char *ans){
    int i;
    int count = 0;
    for(i=0;i<5;i++){
        if (ans[i] == a){
            count++;
        }
    }
    return count;
}