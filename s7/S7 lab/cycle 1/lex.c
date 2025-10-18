#include<stdio.h>
#include<string.h>

int isOperator(char *word){

    char *oper[]={"+","-","*","/","%%","=","<",">","!=","<=",">=","&","|"};
    int len=sizeof(oper)/sizeof(oper[0]);

    for(int i=0;i<len;i++)
        if(strcmp(word,oper[i])==0)
            return 1;

    return 0;
        
    
}

int isKeyWord(char *word){
     char *oper[]={"int","main","long","printf","scanf","if","else","for","return","while","do"};

    for(int i=0;i<11;i++)
        if(strcmp(word,oper[i])==0)
            return 1;

    return 0;
}

int isSymbol(char *word){
     char *oper[]={";","%%","(",")","{","}","","","","","","","",""};
    int len=sizeof(oper)/sizeof(oper[0]);

    for(int i=0;i<len;i++)
        if(strcmp(word,oper[i])==0)
            return 1;

    return 0;
}
int isInteger(char *word){

    char ch=' ';
    for(int i=0;(ch=word[i])!='\0';i++){
        if(ch>='0' && ch<='9')
            return 1;
    }
    return 0;
}

int isIdentifier(char *word){
    if(!(word[0]=='_' || (word[0]>='A' && word[0]<='z')))
        return 0;
    for(int i=1;word[i]!='\0';i++)
        if(!(word[i]=='_' || (word[i]>'A' && word[i]<'z') || (word[i]>'0' && word[i]<'9')))
            return 0;
    return 1;
    
}

void process(char *word){

    if(isOperator(word))
        printf("< %s , operator >\n",word);
    else if(isKeyWord(word))
        printf("< %s , keyword >\n",word);
    else if(isSymbol(word))
        printf("< %s , Symbol >\n",word);
    else if(isInteger(word))
        printf("< %s , Integer >\n",word);
    else if(isIdentifier(word))
        printf("< %s , Identifier >\n",word);
    else {
        word[strcspn(word,"\n")]='\0'; 
        printf("< %s , Invalid >\n",word);
    }
        

        
    
}
void lexit(){
    FILE *fp = fopen("tem.txt","r");

    if(fp == NULL){
        printf("invalid file");
        return;
    }

    char line[250];
    char *word = NULL;

    while(fgets(line,sizeof(line),fp)){
        // puts(line);
        word=strtok(line," ");
        while(word! = NULL){
            if(strcmp(word,"//") == 0||strcmp(word," ") == 0)
                break;
            process(word);
            word=strtok(NULL," ");
        }
    }

}
int main(){
    printf("hello\n");
    lexit();
    return 0;
}