#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a word is an operator
int isOperator(char *word) {
    char *op[] = {"+", "-", "/", "*", "||", "&&", "^", "%", "<", ">", "!=", "==", ">=", "<="};
    int len = sizeof(op) / sizeof(op[0]);

    for (int i = 0; i < len; i++) {
        if (strcmp(word, op[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a word is an identifier
int isIdentifier(char *word) {
    // First character: must be letter or underscore
    if (!(isalpha(word[0]) || word[0] == '_'))
        return 0;

    // Remaining characters: letter, digit, or underscore
    for (int i = 1; word[i] != '\0'; i++) {
        if (!(isalnum(word[i]) || word[i] == '_'))
            return 0;
    }

    return 1;
}

// Function to check if a word is an integer
int isInteger(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i]))
            return 0;
    }
    return 1;
}

// Function to check if a word is a symbol
int isSymbol(char *word) {
    char *symbols[] = {";", "%", "(", ")", "{", "}", "[", "]", ",", ".", ":"};
    int len = sizeof(symbols) / sizeof(symbols[0]);

    for (int i = 0; i < len; i++) {
        if (strcmp(word, symbols[i]) == 0)
            return 1;
    }
    return 0;
}

// Function to check if a word is a keyword
int isKeyword(char *word) {
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

// Process and classify each word
void process(char *word) {
    if (isKeyword(word)) {
        printf("< %s , Keyword >\n", word);
    } else if (isOperator(word)) {
        printf("< %s , Operator >\n", word);
    } else if (isIdentifier(word)) {
        printf("< %s , Identifier >\n", word);
    } else if (isInteger(word)) {
        printf("< %s , Integer >\n", word);
    } else if (isSymbol(word)) {
        printf("< %s , Symbol >\n", word);
    } else {
        printf("< %s , Invalid >\n", word);
    }
}

// Lexical analyzer main logic
void lex() {
    FILE *fp = fopen("tem.txt", "r"); // Fixed filename and mode
    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline
        char *word = strtok(line, " \t"); // Tokenize by space or tab
        while (word != NULL) {
            if (strcmp(word, "//") == 0) // Stop at comments
                break;
            process(word);
            word = strtok(NULL, " \t");
        }
    }

    fclose(fp);
}

// Main function
int main() {
    printf("Start\n");
    lex();
    printf("End\n");
    return 0;
}
