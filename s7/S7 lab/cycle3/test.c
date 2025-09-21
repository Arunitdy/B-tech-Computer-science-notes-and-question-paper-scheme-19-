#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char postfix[100];
char stack[100];
int top = -1;

void dispaly() {
    for (int i = 0; stack[i]; i++) {
        printf("\n %c \n", stack[i]);
    }
    printf("\n");
}


char pop() { return stack[top--]; }
void push(char c) { stack[++top] = c; }
char peek() { return stack[top]; }


int precedance(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void postGenerator(char *infix) {
    printf("\n rhs : %s \n", infix);
    int k = 0;

    for (int i = 0; i < infix[i]; i++) {
        printf("\n %c \n", infix[i]);
        if (!(infix[i] == '*' || infix[i] == '/' || infix[i] == '+' || infix[i] == '-' || infix[i] == '(' || infix[i] == ')')) {
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
            }
            pop();
        } else {
            while (top != -1 && precedance(peek()) >= precedance(infix[i])) {
                postfix[k++] = pop();
            }
            push(infix[i]);
        }
        
        printf("\n post : %s    infix :  %s\n", postfix, infix);
        dispaly();

    }
    while (top != -1) postfix[k++] = pop();
    postfix[k++] = '\0';
    
    printf("\n Postfix = %s\n", postfix);
}

int main() {
    char lhs, rhs[100];
    char infix[100];


    printf("enter the expression :");
    scanf("%s", infix);

    printf("\n %s \n", infix);

    lhs = infix[0];
    strcpy(rhs, infix+2);
    printf("\n %c \n", lhs);

    printf("\n %s \n", rhs);

    postGenerator(rhs);


    return 0;
}