#include <stdio.h>
#include <stdlib.h>

int NFA[10][10], vis[10], close[10];
int n, count;

struct closure_set {
    int count;
    int closure[10];
} element[10];

void accept() {
    printf("Enter the number of states: ");
    scanf("%d", &n);

    // Initialize NFA matrix with 999 (no transition)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            NFA[i][j] = 999;

    int t1;
    printf("Enter the number of transitions: ");
    scanf("%d", &t1);

    printf("Enter transitions in the form FROM SYMBOL TO (-1 for epsilon):\n");
    int from, sym, to;
    for (int i = 0; i < t1; i++) {
        scanf("%d %d %d", &from, &sym, &to);
        NFA[from][to] = sym;  // store symbol (may be -1 for epsilon)
    }
}

void findclose(int s) {
    vis[s] = 1;
    close[count++] = s;

    for (int i = 0; i < n; i++) {
        if (NFA[s][i] == -1 && !vis[i])  // epsilon transition
            findclose(i);
    }
}

void closure() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            vis[j] = 0;

        count = 0;
        findclose(i);

        element[i].count = count;
        for (int k = 0; k < count; k++)
            element[i].closure[k] = close[k];
    }
}

void print_closure() {
    printf("\nEpsilon closures:\n");
    for (int i = 0; i < n; i++) {
        printf("ε-closure(q%d) = { ", i);
        for (int j = 0; j < element[i].count; j++)
            printf("q%d ", element[i].closure[j]);
        printf("}\n");
    }
}

int main() {
    accept();
    closure();
    print_closure();
    return 0;
}
