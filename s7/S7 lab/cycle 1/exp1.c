#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isOperator(char *word){
    char *op[] = {"+", "-", "/", "*", "||", "&&", "^", "%", "<", ">", "!=", "==", ">=", "<="};
    int len = sizeof(op) / sizeof(op[0]);

    for (int i = 0; i < len; i++) {
        if (strcmp(word, op[i]) == 0)
            return 1;
    }
    return 0;
}

int isKeyWord(char *word) {
    char *keywords[] = {
        "int", "main", "long", "printf", "scanf",
        "if", "else", "for", "return", "while", "do"
    };
    int len = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < len; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}


int isSymbol(char *word) {
    char *symbols[] = {";", "%", "(", ")", "{", "}", "[", "]", ",", ".", ":"};
    int len = sizeof(symbols) / sizeof(symbols[0]);

    for (int i = 0; i < len; i++) {
        if (strcmp(word, symbols[i]) == 0)
            return 1;
    }
    return 0;
}

int isInteger(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i]))
            return 0;
    }
    return 1;
}


int isIdentifier(char *word) {
    if (!(isalpha(word[0]) || word[0] == '_')) return 0;

    for (int i = 1; word[i] != '\0'; i++) {
        if (!(isalnum(word[i]) || word[i] == '_'))
            return 0;
    }

    return 1;
}

void process(char *word){

    if(isOperator(word))
        printf("< %s , operator >\n",word);
    else if(isKeyWord(word))
        printf("< %s , keyword >\n",word);
    else if(isSymbol(word))
        printf("< %s , Symbol >\n",word);
    else if(isInteger(word))
        printf("< %s , Integer >\n",word);
    else if(isIdentifier(word))
        printf("< %s , Identifier >\n",word);
    else {
        word[strcspn(word,"\n")]='\0'; 
        printf("< %s , Invalid >\n",word);
    }
}

void lexit() {
   FILE *f1 = fopen("tem.txt", "r");
   if (f1 == NULL) return;
   
   char line[250];
   char *word;
   while (fgets(line, sizeof(line), f1)) {
        word = strtok(line, " ");
        while (word != NULL) {
            if (strcmp(word, "//") == 0) break;
            process(word);
            word = strtok(NULL, " ");
        }
   }
   fclose(f1);
}

int main(){
    printf("hello\n");
    lexit();
    return 0;
}