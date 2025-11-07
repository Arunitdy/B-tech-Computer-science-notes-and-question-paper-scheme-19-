#include <stdio.h>
#include <stdlib.h>
char stack[100];
int top = -1, ip;
char tempvari = 'T';

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top != -1) return stack[top--];
    return '0';
}

char peek() {
    if (top != -1) return stack[top];
    return '0';
}
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {
            push(infix[i]);
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top != -1 && peek != '(') postfix[k++] = pop();
            pop();
        } else {
            while (top != -1 && precedense(peek()) <= precedense(infix[i])) postfix[k++] = pop();
            postfix[k++] = infix[i];
        }
    }

    while (top != -1) postfix[k++] = pop();
    postfix[k] = '\0';
}

char generate (char a, char b, char op) {
    char temp = tempvari; 
    
    if (a == '\0' || b == '\0') {
        printf("\n invalid \n");
    } else if (op == '+') {
        printf("MOV AX, %c\n", a);
        printf("ADD AX, %c\n", b);
        printf("MOV %c, AX\n", res);
    } else if (op == '-') {
        printf("MOV AX, %c\n", a);
        printf("SUB AX, %c\n", b);
        printf("MOV %c, AX\n", res);
    } else if (op == '*') {
        printf("MOV AX, %c\n", a);
        printf("MUL %c\n", b);
        printf("MOV %c, AX\n", res);
    } else if (op == '/') {
        printf("MOV AX, %c\n", a);
        printf("DIV %c\n", b);
        printf("MOV %c, AX\n", res);
    }
    return res;
}

int main() {
    char input[100], lhs, rhs[100], postfix[100];
    printf("enter the input exprestion:");
    scanf("%s", input);
    lhs = input[0];
    strcpy(rhs, input + 3);

    infixToPostfix(rhs, postfix);
    
    printf("\n--- Three Address Code (TAC) ---\n");
    printf("--- 8086 Assembly Code ---\n");
    char stack2[100];
    t = -1;

    for (int i = 0; postfix[i]; i++) {
        if (isalnum(postfix[i])) {
            stack2[++t] = postfix[i];
        } else {
            char a = stack2[t--];
            char b = stack2[t--];
            char res = generate(a, b, postfix[i]);
            stack2[++t] = res;
        }
    }


}