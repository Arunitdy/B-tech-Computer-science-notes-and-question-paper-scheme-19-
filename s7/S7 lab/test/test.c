#include <stdio.h>

#define N 10
#define M 10

int NFA[N][M][N], DFA[1<<N][M], vis[1<<N], final[N];

int n, m, start;

void accept() {
    printf("enter the number of states:");
    scanf("%d", &n);

    printf("enter the number of input symbols:");
    scanf("%d", &start);

    int tem1,tem2,a,b,c;
    printf("enter the number of final state :");
    scanf("%d",&tem1);

    printf("enter the final states : \n");
    while(tem1--){
        scanf("%d",&tem2);
        final[tem2]=1;
    }

     printf("enter the number of transition :");
    scanf("%d",&tem1);

    printf("enter the transitions in the format from - sym - to \n");
    while(tem1--){
        scanf("%d %d %d",&a,&b,&c);
        NFA[a][b][c]=1;
    }
}

void conv() {
    int q[1<<N], f = -1, r = -1;
    
}


int main() {

    accept();
    conv();
    disp();

    return 0;

}