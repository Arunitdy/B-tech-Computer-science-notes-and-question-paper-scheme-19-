 #include<stdio.h>

int NFA[10][10][10],newNFA[10][10][10],epsi[10][10];

int vis[10],close[10],count,n,m;

struct meyamo {
    int count;
    int closure[10];
} element[10];

void accept() {
    printf("enter the number of states :");
    scanf("%d",&n);

    printf("enter the number of symbols : ");
    scanf("%d",&m);
    int t1,from,to,sym;
    printf("enter the number of transitions : ");
    scanf("%d",&t1);

    printf("enter the transitions in the form from - sym -to(-1 for epsilon)\n");
    while(t1--) {
        scanf("%d %d %d",&from,&sym,&to);
        if (sym == -1)
            epsi[from][to] = 1;
        else 
            NFA[from][sym][to] = 1;
    }
}

void DFS(int s) {
    vis[s] = 1;
    close[count++] = s;
    for (int i = 0; i < n; i++) {
        if(epsi[s][i] == 1 && !vis[i])
            DFS(i);
    }
}
void closure(){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            vis[j]=0;
        count=0;
        DFS(i);

        element[i].count=count;
        for(int k=0;k<count;k++)
            element[i].closure[k]=close[k];
    }

    printf("closure\n\n");

    for(int i=0;i<n;i++){
        printf("q%d -> { ",i);

        for(int j=0;j<element[i].count;j++)
            printf(" q%d ,",element[i].closure[j]);
        printf("}\n");
    }
}

void conv(){
    for(int s=0;s<n;s++){
        for(int a=0;a<m;a++){
            for(int i = 0;i<element[s].count;i++){
                int q = element[s].closure[i];
                for(int j=0;j<n;j++){
                    if(NFA[q][a][j]){
                        for(int l=0;l<element[j].count;l++){
                            newNFA[s][a][element[j].closure[l]]=1;
                        }
                    }
                }
            }
        }
    }
}

void prin(){

    for(int s=0;s<n;s++){
        printf(" q%d ->  ",s);
        for(int a=0;a<m;a++){
            printf(" | %d -> {",a);
            for(int j=0;j<n;j++){
                if(newNFA[s][a][j])
                    printf(" q%d ,",j);
            }
            printf("}");
        }
        printf("\n");
    }
}
int main(){

    accept();
    closure();
    conv();
    prin();

    return 0;
}