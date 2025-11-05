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

void conv(){
    int q[1<<N],f=-1,r=-1;
    q[r++]=1<<start,vis[1<<start]=1;

    while(f<r){
        int s=q[f++];
        for(int a=0;a<m;a++){
            int ns=0;
            for(int i=0;i<n;i++){
                if(s&(1<<i)){
                    for(int j=0;j<n;j++){
                        if(NFA[i][a][j]){
                            ns|=(1<<j);
                        }
                    }
                }
            }
            DFA[s][a]=ns;
            if(ns && !vis[ns]){
                vis[ns]=1;
                q[r++]=ns;
            }
        }
        

    }
}

void prin(int s){
    printf("{ ");
    for(int i=0;i<n;i++)
        if(s &(1<<i)) printf("q%d ",i);

    printf("}");
    
}
void disp(){
    for(int s=0;s<(1<<N);s++){
        if(vis[s]){
            prin(s);
            printf(" = ");
            for(int a=0;a<m;a++){
                printf(" | %d -> ",a);
                prin(DFA[s][a]);;
            }
            printf("\n");
        }
    }
}

int main(){

    accept();
    conv();
    disp();

    return 0;
}