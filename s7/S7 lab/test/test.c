#include <stdio.h>
int m, n, t;
char q[10], NFA[10][10][10], DFA[1<<10][10], vis[1<<10];
int start;

void accept() {
    printf("Enter the number of states:");
    scanf("%d", &n);

    printf("Enter the number of symbols:");
    scnaf("%d", &m);

    printf("Enter the number of trancition:");
    scanf("%d", &t);
    
    int from, to, sym;

    for (int i = 0; i < t; i++) {
        scanf("%d %d %d", &from, &sym, &to);
        NFA[from][sym][to] ;
    }
}
void DFA() {
    int r = -1, f = -1;
    q[r++] = 1 << start;
    vis[1<<start] = 1;

    while (f < r) {
        s = q[f++];
        for (int a = 0; a < m; a++) {
            int ns = 0;
            for (int i = 0; i < n; i++) {
                if (s & (1<<i)) {
                    for (int j = 0; j < n; j++) {
                        if (NFA[i][a][j]) ns |= (1 << j);
                    }
                }
            }
            DFS[s][a] = ns;
            if (!vis[ns]) {
                vis[ns] = 1;
                q[r++] = ns;
            }
        }
    }
}
void prin(int s) {
    for (int i = 0; i < n; i++) if (s & (1<<i)) printf("q%d ", i);
}

void display() {
    for (int i = 0; i <(1<<10); i++) {
        if (vis[s]) {
            prin(s);
            for (int a = 0; a < m; a++) {
                printf("a");
                prin(DFS[s][a]);
            }
        }
    }
}
int main() {
    accept();
}