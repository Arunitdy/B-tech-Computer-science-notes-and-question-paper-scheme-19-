#include <stdio.h>
#include <string.h>
#include <ctype.h>

char postfix[100];
char stack[100];
int top = -1;

char pop() {return stack[top--];}
void push(char c) {stack[++top] = c;}
char peek() {return stack[top];}

int prefix(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
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
    while(top != -1) postfix[k++] = pop();
    
    printf("%s\n", postfix);
}
void TAC () {
    char stack2[100][100];
    int t2 = -1;
    int t = 0;

    for (int i = 0; postfix[i]; i++) {
        if (!(postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '/' || postfix[i] == '*' || postfix[i] == '(' || postfix[i] == ')')) {
            
            sprintf(stack2[++t2], "%c",postfix[i]);
        } else {
            char a[10], b[10], c[10];
            strcpy(a, stack2[t2--]); // right operand
            strcpy(b, stack2[t2--]); // left operand

            sprintf(c, "t%d", t++);

            printf("%s = %s %c %s", c, b, postfix[i], a);
            strcpy(stack2[++t2], c);

        }
    }
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
    TAC();
    return 0;
}