#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[100];
int i = 0;

void error();
void match();
void E();
void F();
void T();
void Tprime();
void Eprime();


void error() {
    printf("error");
    exit(i);
}

void match(char ch) {
    if (input[i] == ch) {
        i++;
    } else {
        error();
    }
}

void Tprime() {
    if (input[i] == '*') {
        match('*');
        F();
        Tprime();
        
    }
}

void F() {
    if (input[i] == '(') {
        match('(');
        E();
        match(')');
    } else if (input[i] == 'i') {
        match('i');
    } else {
        error();
    }
}

void Eprime() {
    if (input[i] == '+') {
        match('+');
        T();
        Eprime();
    } 
}

void T() {
    F();
    Tprime();
}

void E() {
    T();
    Eprime();
}

int main() {
    printf("enter the input:");
    scanf("%s", input);
    strcat(input, "$");
    E();
    if (input[i] == '$') {
        printf("accept");
    } else {
        printf("error");
    }
}