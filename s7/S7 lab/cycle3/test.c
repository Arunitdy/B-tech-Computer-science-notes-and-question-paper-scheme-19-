#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main() {
    char lhs, rhs[100];
    char postfix[100];


    printf("enter the expression :");
    scanf("%s", postfix);

    printf("\n %s \n", postfix);

    lhs = postfix[0];
    strcpy(rhs, postfix+2);
    printf("\n %c \n", lhs);
    printf("\n %s \n", rhs);

    return 0;
}