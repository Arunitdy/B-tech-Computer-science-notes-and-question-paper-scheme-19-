#include<stdio.h>

#define N 10
#define M 10

int NFA[N][M][N],DFA[1<<N][M],vis[1<<N],final[N];
int n,m,start;

void accept() {
    printf("enter the number of states :");
    scanf("%d",&n);

    printf("enter the number of input symbols :");
    scanf("%d",&m);

    printf("enter the start state :");
    scanf("%d",&start);

    int tem1, a, b, c;

    printf("enter the number of transition :");
    scanf("%d",&tem1);

    printf("enter the transitions in the format from - sym - to \n");
    while(tem1--){
        scanf("%d %d %d",&a,&b,&c);
        NFA[a][b][c] = 1;
    }
}

void con() {
    int que[1 << n], r = -1,  f = -1;
    
    que[r++] = 1<<start;

    while (f < r) {
        int s = que[f++];
        for (int a = 0 ; a < n; a++) {
            int ns = 0;
            for (int i = 0; i < 1<<n; i++) {
                if (s & (1<<i)) {
                    for (int k = 0; k < n; k++) {
                        if (nfa[i][a][j]) ns |= i<<k;
                    }
                }
            }

            dfs[ns] = 1;
            if (vis[i] && ns) {
                vis[ns] = 1;
                g[r++] = ns
            }
        }
    }
}