#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Structure to hold assignment statements
struct Statement {
    char lhs;
    char rhs1;
    char rhs2;
    char op;
    int isConst; // 1 if rhs1 is constant
    int constVal;
};

int main() {
    int n, i, j;
    struct Statement stmts[MAX];
    int constTable[26]; // store constant values for variables
    int knownConst[26]; // 1 if variable has a known constant

    // Initialize
    for (i = 0; i < 26; i++) {
        knownConst[i] = 0;
    }

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter statements (e.g., a = 5 OR b = a + 3):\n");
    for (i = 0; i < n; i++) {
        char lhs, eq, rhs1, rhs2, op;
        char buffer[20];

        scanf(" %[^\n]", buffer);

        lhs = buffer[0];
        eq = buffer[2];

        if (isdigit(buffer[4])) {
            // form: a = 5
            stmts[i].lhs = lhs;
            stmts[i].isConst = 1;
            stmts[i].constVal = buffer[4] - '0';
        } else if (isalpha(buffer[4]) && strlen(buffer) > 5) {
            // form: a = b + 3 or a = b + c
            stmts[i].lhs = lhs;
            stmts[i].isConst = 0;
            stmts[i].rhs1 = buffer[4];
            stmts[i].op = buffer[6];
            stmts[i].rhs2 = buffer[8];
        } else {
            // form: a = b
            stmts[i].lhs = lhs;
            stmts[i].isConst = 0;
            stmts[i].rhs1 = buffer[4];
            stmts[i].op = '\0';
            stmts[i].rhs2 = '\0';
        }
    }

    printf("\n--- Optimized Code After Constant Propagation ---\n");

    for (i = 0; i < n; i++) {
        if (stmts[i].isConst) {
            // Direct constant assignment
            constTable[stmts[i].lhs - 'a'] = stmts[i].constVal;
            knownConst[stmts[i].lhs - 'a'] = 1;
            printf("%c = %d\n", stmts[i].lhs, stmts[i].constVal);
        } else if (stmts[i].op == '\0') {
            // Simple copy: a = b
            if (knownConst[stmts[i].rhs1 - 'a']) {
                int val = constTable[stmts[i].rhs1 - 'a'];
                printf("%c = %d\n", stmts[i].lhs, val);
                constTable[stmts[i].lhs - 'a'] = val;
                knownConst[stmts[i].lhs - 'a'] = 1;
            } else {
                printf("%c = %c\n", stmts[i].lhs, stmts[i].rhs1);
            }
        } else {
            // Expression: a = b + c
            int const1 = 0, const2 = 0, val1, val2;
            if (isalpha(stmts[i].rhs1) && knownConst[stmts[i].rhs1 - 'a']) {
                const1 = 1;
                val1 = constTable[stmts[i].rhs1 - 'a'];
            } else if (isdigit(stmts[i].rhs1)) {
                const1 = 1;
                val1 = stmts[i].rhs1 - '0';
            }

            if (isalpha(stmts[i].rhs2) && knownConst[stmts[i].rhs2 - 'a']) {
                const2 = 1;
                val2 = constTable[stmts[i].rhs2 - 'a'];
            } else if (isdigit(stmts[i].rhs2)) {
                const2 = 1;
                val2 = stmts[i].rhs2 - '0';
            }

            if (const1 && const2) {
                int result;
                switch (stmts[i].op) {
                    case '+': result = val1 + val2; break;
                    case '-': result = val1 - val2; break;
                    case '*': result = val1 * val2; break;
                    case '/': result = (val2 != 0) ? val1 / val2 : 0; break;
                    default: result = 0;
                }
                printf("%c = %d\n", stmts[i].lhs, result);
                constTable[stmts[i].lhs - 'a'] = result;
                knownConst[stmts[i].lhs - 'a'] = 1;
            } else {
                // Not fully constant
                printf("%c = %c %c %c\n", stmts[i].lhs, stmts[i].rhs1, stmts[i].op, stmts[i].rhs2);
            }
        }
    }

    return 0;
}