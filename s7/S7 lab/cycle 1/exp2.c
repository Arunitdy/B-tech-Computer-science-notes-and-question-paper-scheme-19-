#include<stdio.h>


int NFA[10][10],vis[10],close[10];

int n,count;

struct closs{
    int count;
    int closure[10];
} element[10];

void accept(){
    printf("enter the number of states :");
    scanf("%d",&n);

    int t1,t2;
    printf("enter the number of transitions :");
    scanf("%d",&t1);

    printf("enter the transitions in FROM - SYM - TO,(-1 for epsilon)\n");
    int a,b,c;

    while(t1--){
        scanf("%d %d %d",&a,&b,&c);
        NFA[a][c]=b;
    }
}

void findclose (int s) {
    vis[s]=1;
    close[count++]=s;
    for(int i=0;i<n;i++){
        if(NFA[s][i]==-1 && !vis[i])
            findclose(i);
    }
}

void closure() {
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++)
            vis[j]=0;
        count=0;

        findclose(i);

        element[i].count=count;
        for(int k=0;k<count;k++){
            element[i].closure[k]=close[k];
        }
    }
}

void prin(){

    for(int i=0;i<n;i++){
        printf(" q%d -> { ",i);

        for(int j=0;j<element[i].count;j++)
            printf(" q%d, ",element[i].closure[j]);
        printf("}\n");
    }
}

int main() {
    +
    accept();
    closure();
    prin();
    
    return 0;
}