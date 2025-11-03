#include <stdio.h>
#include <sdlib.h>
#include <string.h>
#include <ctype.h>
int isOperator (char *word) {
    
}

int isIdentifir(char *word) {

}

int isInteger(char *word) {

}

int Symbol(char *word) {

}

void process(char *word) {
    if (isOperator(word)) {
        printf("< %s ,operator >", word);
    } else if (isIdentifir(word)) {
        printf("< %s ,identifir >", word);
    }  else if (isInteger(word)) {
        printf("< %s ,Integer >", word);
    } else if (isSymbol(word)) {
        printf("< %s ,Symbol >", word);
    } else {
        printf("< %s ,invalid >", word);
    }
}

void lex() {
    FILE *f1 = fopen("te,.txt", 'r');
    if (f1 == NULL) return;
    char line[300];

    char *word[] = NULL;
    while (fgets(line, sizeof(line), fp)!= 0) {
        word = strtok(line, " ");
        while (word != NULL) {
            if (strcmp(word, "//") == 0 || strcmp(word, "/0") == 0) break;
            process(word);
            word = strtok(NULL, " ");
        }
    }
}

int main () {
    printf("start");
    lex();
    printf("end");
    return 0;
}