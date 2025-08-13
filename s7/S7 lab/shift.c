#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

int z = 0, i = 0, j = 0, c = 0, n = 0;
char a[MAX], ac[30], stk[MAX], act[10];
char prod[10][10]; 
void check() {
    strcpy(ac, "REDUCE TO ");

    for (int p = 0; p < n; p++) {
        int len = strlen(prod[p]) - 3; 
        char *rhs = prod[p] + 3;       
        for (z = 0; z <= i - len + 1; z++) {
            if (strncmp(stk + z, rhs, len) == 0) {
                printf("%s%s", ac, prod[p]);
                stk[z] = prod[p][0]; 
                stk[z + 1] = '\0';
                i = z;
                printf("\n$%s\t%s$\t", stk, a);
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar(); 
    printf("Enter productions (e.g., E->2E2):\n");
    for (int k = 0; k < n; k++) {
        fgets(prod[k], sizeof(prod[k]), stdin);
        prod[k][strcspn(prod[k], "\n")] = '\0'; 
    }

    printf("Enter input string: ");
    scanf("%s", a);
    c = strlen(a);

    strcpy(act, "SHIFT");

    printf("\nStack\tInput\tAction\n");
    printf("$\t%s$\t", a);

    for (i = 0, j = 0; j < c; i++, j++) {
        printf("%s", act);
        stk[i] = a[j];
        stk[i + 1] = '\0';
        a[j] = ' ';
        printf("\n$%s\t%s$\t", stk, a);
        check();
    }

    check();

    if (stk[0] == prod[0][0] && stk[1] == '\0')
        printf("Accept\n");
    else
        printf("Reject\n");

    return 0;
}



