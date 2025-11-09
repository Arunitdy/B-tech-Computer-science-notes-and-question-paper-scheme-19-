#include <stdio.h>

int n, m, start;
int NFA[10][10][10], DFA[1<<10][10] q[1<<10], vis[1<<10];

void accept() {
    printf("enter the number of states :");
    scanf("%d",&n);

    printf("enter the number of input symbols :");
    scanf("%d",&m);

    printf("enter the start state :");
    scanf("%d",&start);

    int tem1,tem2,a,b,c;
    printf("enter the number of final state :");
    scanf("%d",&tem1);


    printf("enter the number of transition :");
    scanf("%d",&tem1);

    printf("enter the transitions in the format from - sym - to \n");
    while(tem1--){
        scanf("%d %d %d",&a,&b,&c);
        NFA[a][b][c]=1;
    }
}

void con() {
    int f = -1, r = -1;
    q[r++] = 1<<start;
    vis[1<<start] = 1;

    while(f < r) {
        int s = q[f++];

        for (int a = 0; a < m; a++) {
            int ns = 0;
            for (int i = 0; i < n; i++) {
                if (s & (1<<i)) {
                    for (int j = 0; j < n; j++) {
                        if (NFA[i][a][j]) {
                            ns |= (1<<j);
                        }
                    }
                }
            }

            DFS[s][a] = ns;
            if (ns && !vis[ns]) {
                vis[ns] = 1;
                q[r++] = ns;
            }
        }
    }
}


void prin(int s) {
    for (int i = 0; i < n; i++) {
        if (s & (1<<i)) printf("%dq", i);
    }
}

void displai() {
    for (int s = 0; s < 1<<n; s++) {
       if (vis[s]){     prin(s);
            for (int a = 0; a < m; a++) {
                printf("a"); prin(dfa[s][a]);
            }}
    }
}



int main() {

}