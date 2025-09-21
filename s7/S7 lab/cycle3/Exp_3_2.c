#include <stdio.h>
#include<stdlib.h>
#include <string.h>

char input[100];
int i = 0;

// Function prototypes
void E();
void Eprime();
void T();
void Tprime();
void F();

void error() {
    printf("Error at position %d\n", i + 1);
    exit(1);
}

// Match terminal
void match(char expected) {
    if (input[i] == expected) {
        i++;
    } else {
        error();
    }
}

// E -> T E'
void E() {
    T();
    Eprime();
}

// E' -> + T E' | e
void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    }
    // else e, do nothing
}

// T -> F T'
void T() {
    F();
    Tprime();
}

// T' -> * F T' | e
void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
    }
    // else e, do nothing
}

// F -> (E) | id
void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else if (input[i] == 'i') {
        match('i'); // Simulate "id" with single character 'i'
    } else {
        error();
    }
}

int main() {
    printf("Enter the input string (use 'i' for id): ");
    scanf("%s", input);
    strcat(input, "$");  // End of input marker

    E();  // Start parsing from E

    if (input[i] == '$') {
        printf("Input string is accepted.\n");
    } else {
        error();
    }

    return 0;
}
