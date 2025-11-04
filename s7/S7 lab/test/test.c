#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void E();
void Eprime();
void T();
void Tprime();
void F();

char input[100];
int i = 0;
void match(char c) {
    if (c == input[i]) {
        i++;
    } else {
        printf("invalid");
        exit(1);
    }
}
void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else {
        match('i');
    }
}
void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
    }
}
void T() {
    F();
    Tprime();
}
void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    }
    
}
void E() {
    T();
    Eprime();
}



int main() {
    printf("enter the input:");
    scanf("%s", input);
    strcat(input, "&");
    E();
    if (input[i] == '&') {
        printf("valid");
    } else {
        printf("invalid");
    }
    
}