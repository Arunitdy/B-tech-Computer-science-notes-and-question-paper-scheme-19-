#include<stdio.h>

int DFA[10][10],rep[10];
int n,m,final[10];
int mark[10][10]={0};
void accept () {
    int t1,t2;

    printf("enter the number of states in DFA :");
    scanf("%d",&n);

    printf("enter the number of symbolsin DFA :");
    scanf("%d",&m);

    printf("enter the number of final state :");
    scanf("%d",&t1);

    
    printf("enter the final states");
    while (t1--) {
        scanf("%d",&t2);
        final[t2]=1;
    }

    printf("enter the transitions\n :");
    for (int i=0;i<n;i++) {
        for (int a=0;a<m;a++) {
            printf("transi(%d,%d)-> : ",i,a);
            scanf("%d",&DFA[i][a]);
        }
    }
    
}

void fillmark() {

    for (int i=0;i<n;i++) {
        for (int j=0;j<i;j++) {
            if (final[i]!=final[j]) {
                mark[i][j]=1;
            }
        }
    }

    int change=1;
    while (change) {
        change=0;
        for (int i=0;i<n;i++) {
            for (int j=0;j<i;j++) {
                if (!mark[i][j]) {
                    for (int k=0;k<m;k++) {
                        int a=DFA[i][k];
                        int b=DFA[j][k];

                        if (a==b) continue;
                        if (a<b) {int t=a;a=b;b=t;}
                        if (mark[a][b] == 1) {
                            mark[i][j] = 1;
                            change=1;
                            break;
                        }
                    }
                }
            }
        }
    }

    printf("Equivalent states:\n"); 

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < i; j++) { 
            if (mark[i][j]!=1) { 
                printf("State %d and %d are equivalent.\n", i, j); 
            } 
        } 
    } 
}

void newtrans() {
    for (int i=0;i<n;i++) rep[i]=i;
    for (int i=0;i<n;i++) {
        for (int j=0;j<i;j++) {
            if (mark[i][j]!=1) {
                rep[i]=rep[j];
            }
        }
    }
}

void prin(){
    for(int i=0;i<n;i++){
        if(rep[i]==i){
            printf(" state {");
            for(int j=0;j<n;j++){
                    if(rep[j]==i)
                        printf(" q%d ,",j);
            }
            printf("} = ");
            for(int a=0;a<m;a++){
                printf("| %d -> %d",a,rep[DFA[i][a]]);
            }
            printf("\n");
        }
    }
}

int main(){
    accept();
    fillmark();
    newtrans();
    prin();
}