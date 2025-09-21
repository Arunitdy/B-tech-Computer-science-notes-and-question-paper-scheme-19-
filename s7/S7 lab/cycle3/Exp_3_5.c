#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int tempCount = 1;

// Stack for operators
char stack[MAX];
int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
char peek() { return stack[top]; }

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
            while (top != -1 && peek() != '(')
                postfix[k++] = pop();
            pop(); // remove '('
        } else { // operator
            while (top != -1 && precedence(peek()) >= precedence(infix[i]))
                postfix[k++] = pop();
            push(infix[i]);
        }
    }
    while (top != -1) postfix[k++] = pop();
    postfix[k] = '\0';
}

// Generate TAC from postfix
void generateTAC(char* postfix, char lhs) {
    char stack2[MAX][10];
    int t2 = -1;
    char buf[10];

    printf("\nThree Address Code (TAC):\n");

    for (int i = 0; postfix[i]; i++) {
        if (isalnum(postfix[i])) {
            sprintf(stack2[++t2], "%c", postfix[i]);
        } else {
            char b[10], a[10], res[10];
            strcpy(b, stack2[t2--]);
            strcpy(a, stack2[t2--]);
            sprintf(res, "t%d", tempCount++);

            printf("%s = %s %c %s\n", res, a, postfix[i], b);

            strcpy(stack2[++t2], res);
        }
    }
    printf("%c = %s\n", lhs, stack2[t2]);
}

int main() {
    char expr[100], rhs[100], postfix[100];
    char lhs;

    printf("Enter expression (e.g., a=b+c*d): ");
    scanf("%s", expr);
    printf("\n %s \n", expr);

    lhs = expr[0];              // left-hand side variable
    strcpy(rhs, expr + 2);      // right-hand side expression

    
    printf("\n %s  \n", rhs);
    
    printf("\n %c  \n", lhs);

    infixToPostfix(rhs, postfix);

    printf("\nPostfix: %s\n", postfix);
    generateTAC(postfix, lhs);

    return 0;
}
