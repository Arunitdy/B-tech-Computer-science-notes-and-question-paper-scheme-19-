#include <stdio.h>
#include <stdlib.h>

int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    int k = 0, t = 0;
    char stack[100];

    for (int i = 0; i < infix[i]; i++) {
        if (isalnumop()){
            postfix[k++] = infix[i];
        } else if (infix[i] == '(') {
            stack[t++] = infix[i];
        } else if (infix[i] == ')') {
            while (t != -1 && stack[t] != '(') postfix[k++] = stack[t--];
            stack[t--];
        } else {
            while (t > -1 && precedence(stack[t]) >= precedence(stack[t])) postfix[k++] = stack[t--];
            stack[t++] = infix[i]; 
        }
    }
    while (t != -1) postfix[k++] = stack[t--];
}

int main() {
    
    char input[100], postfix[100];
    print("enter the expresion:");
    scanf("%s", infix);

    char lhs = infix[0];
    char rhs[100];
    strcpy(rhs, infix + 2);

    printf("%s", rhs);
    printf("%s", lhs);

    infixToPostfix(rhs, postfix);



}