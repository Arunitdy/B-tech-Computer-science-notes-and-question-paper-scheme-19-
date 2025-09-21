#include <stdio.h>
#include <string.h>
#include <ctype.h>

char postfix[100];
char stack[100];
int top = -1;

char pop() {return stack[top--];}
void push(char c) {stack[top++] = c;}
char peek() {return stack[top];}

int prefix(char c) {
    if (c == '*' || c == '/') return 1;
    if (c == '+' || c == '-') return 2;
    return 0;
}


void postfixConv(char *rhs) {
    int  k = 0;

    for (int i = 0; rhs[i]; i++) {
        if (!(rhs[i] == '+' || rhs[i] == '-' || rhs[i] == '/' || rhs[i] == '*' || rhs[i] == '(' || rhs[i] == ')')) {
            postfix[k++] = rhs[i];
        } else if (rhs[i] == '(') {
            push(rhs[i]);
        } else if (rhs[i] == ')') {
            while (top != -1 && peek() != '(') {
                postfix[k++] = pop();
            }
            pop();
        } else {
            while (top != -1 && prefix(peek()) >= prefix(rhs[i])) {
                postfix[k++] = pop();
            }
            push(rhs[i]);

        }
    }
    while(top != -1 ) {
        postfix[k++] = pop();
    }
    printf("%s\n", postfix);
}

int main() {
    char infix[100];
    printf("enter the expr:");
    scanf("%s", infix);
    char lhs = infix[0];
    char rhs[100];
    strcpy(rhs, infix+2);

    printf("%c , %s\n", lhs, rhs);

   postfixConv(rhs);

    return 0;
}