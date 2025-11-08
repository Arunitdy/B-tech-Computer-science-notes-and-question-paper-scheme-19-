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

void con () {
    int f = -1, r = -1;
    vis[1<<start] = 1;
    
}





int main() {

}