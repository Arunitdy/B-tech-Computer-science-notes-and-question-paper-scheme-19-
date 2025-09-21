#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

char tempVar = 'T'; // for naming temporaries

// Stack for operators
char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Convert infix to postfix
void infixToPostfix(char* infix, char* postfix) {
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {  // operand
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        } else { // operator
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i]))
                postfix[k++] = pop();
            push(infix[i]);
        }
    }
    while (top != -1) postfix[k++] = pop();
    postfix[k] = '\0';
}

// TAC + Assembly generation
char generate(char a, char b, char op) {
    char res = tempVar++;
    printf("%c = %c %c %c\n", res, a, op, b);  // TAC

    // Assembly
    if (op == '+') {
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
    char expr[100], postfix[100];
    char lhs, rhs[100];

    printf("Enter expression (e.g., a=b+c*d): ");
    scanf("%s", expr);

    lhs = expr[0];             // left side variable
    strcpy(rhs, expr + 2);     // right side

    infixToPostfix(rhs, postfix);

    printf("\n--- Three Address Code (TAC) ---\n");
    printf("--- 8086 Assembly Code ---\n");

    // Postfix evaluation with TAC generation
    char stack2[MAX];
    int t2 = -1;
    for (int i = 0; postfix[i]; i++) {
        if (isalnum(postfix[i])) {
            stack2[++t2] = postfix[i];
        } else {
            char b = stack2[t2--];
            char a = stack2[t2--];
            char res = generate(a, b, postfix[i]);
            stack2[++t2] = res;
        }
    }
    printf("%c = %c\n", lhs, stack2[t2]);

    return 0;
}
