#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char input[100];
int i = 0;

void E();

bool match(char expected) {
    if (input[i] == expected) {
        i++;
        return true;
    } else {
        return false;
    }
}

void F() {
    if (match('(')) {
        E();
        if (!match(')')) {
            printf("\n error \n");
        }
    } else {
        if (!match('i')) {
            printf("\n error \n");
        }
    }
}

void Tprime() {
    if (match('*')) {
        F();
        Tprime();
    }
}

void T() {
    F();
    Tprime();
}

void Eprime() {
    if (match('+')) {
        T();
        Eprime();
    }
}

void E() {
    T();
    Eprime();
}


int main () {
    printf("Hello, World!\n");

    printf("enter an expression: ");
    scanf("%s", input);
    strcat(input, "$");

    E();

    if (input[i] == '$') {
        printf("String accepted\n");
    } else {
        printf("String not accepted\n");    
    }


    return 0;
}

/*

E -> T E'
E' -> + T E' | e
T -> F T'
T' -> * F T' | e
F -> ( E ) | id



*/