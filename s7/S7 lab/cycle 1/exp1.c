#include<stdio.h>
#include<string.h>

int isOperator(char *word) {

    char *oper[]={"+","-","*","/","%%","=","<",">","!=","<=",">=","&","|"};
    int len=sizeof(oper)/sizeof(oper[0]);

    for(int i=0;i<len;i++)
        if(strcmp(word,oper[i])==0)
            return 1;
    return 0;
}

int isKeyWord(char *word) {
    char *oper[]={"int","main","long","printf","scanf","if","else","for","return","while","do"};
    for(int i=0;i<11;i++)
        if(strcmp(word,oper[i])==0)
            return 1;
    return 0;
}

int isSymbol(char *word) {
     char *oper[]={";","%%","(",")","{","}","","","","","","","",""};
    int len=sizeof(oper)/sizeof(oper[0]);

    for(int i=0;i<len;i++)
        if(strcmp(word,oper[i])==0)
            return 1;

    return 0;
}

int isInteger(char *word) {

    char ch=' ';
    for (int i=0;(ch=word[i])!='\0';i++) {
        if(ch>='0' && ch<='9')
            return 1;
    }
    return 0;
}

int isIdentifier(char *word) {
    if(!(word[0]=='_' || (word[0]>='A' && word[0]<='z')))
        return 0;
    for(int i=1;word[i]!='\0';i++)
        if(!(word[i]=='_' || (word[i]>'A' && word[i]<'z') || (word[i]>'0' && word[i]<'9')))
            return 0;
    return 1;
    
}

void process(char *word) {

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

void lexit() {
    FILE *fp = fopen("tem.txt","r");

    if(fp == NULL) {
        printf("invalid file");
        return;
    }

    char line[250];
    char *word = NULL;

    while(fgets(line,sizeof(line),fp)) {
        // puts(line);
        printf("\n%s\n", line);
        word = strtok(line," ");
        while (word != NULL) {
            if(strcmp(word,"//") == 0 || strcmp(word," ") == 0)
                break;
            printf("\n%s\n", word);
            process(word);
            word = strtok(NULL," ");
        }
    }
}

int main() {
    printf("hello\n");
    lexit();
    return 0;
}



/*
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isOperator(char *word) {
    char *oper[] = {"+", "-", "*", "/", "%", "=", "<", ">", "!=", "<=", ">=", "&&", "||"};
    int len = sizeof(oper) / sizeof(oper[0]);
    for (int i = 0; i < len; i++)
        if (strcmp(word, oper[i]) == 0)
            return 1;
    return 0;
}

int isKeyword(char *word) {
    char *oper[] = {"int", "main", "long", "printf", "scanf", "if", "else", "for", "return", "while", "do"};
    int len = sizeof(oper) / sizeof(oper[0]);
    for (int i = 0; i < len; i++)
        if (strcmp(word, oper[i]) == 0)
            return 1;
    return 0;
}

int isSymbol(char c) {
    char symbols[] = {';', '(', ')', '{', '}', '[', ']', ',', '.'};
    for (int i = 0; i < sizeof(symbols); i++)
        if (c == symbols[i])
            return 1;
    return 0;
}

int isInteger(char *word) {
    if (word[0] == '\0') return 0;
    for (int i = 0; word[i] != '\0'; i++)
        if (!isdigit(word[i]))
            return 0;
    return 1;
}

int isIdentifier(char *word) {
    if (!(isalpha(word[0]) || word[0] == '_'))
        return 0;
    for (int i = 1; word[i] != '\0'; i++)
        if (!(isalnum(word[i]) || word[i] == '_'))
            return 0;
    return 1;
}

void process(char *word) {
    if (isKeyword(word))
        printf("< %s , Keyword >\n", word);
    else if (isOperator(word))
        printf("< %s , Operator >\n", word);
    else if (isInteger(word))
        printf("< %s , Integer >\n", word);
    else if (isIdentifier(word))
        printf("< %s , Identifier >\n", word);
    else if (word[0] == '"' && word[strlen(word) - 1] == '"')
        printf("< %s , String Literal >\n", word);
    else
        printf("< %s , Invalid >\n", word);
}

void tokenizeLine(char *line) {
    int i = 0, j = 0;
    char token[100];
    int len = strlen(line);

    while (i < len) {
        // Skip spaces
        if (isspace(line[i])) {
            i++;
            continue;
        }

        // Handle string literals
        if (line[i] == '"') {
            j = 0;
            token[j++] = line[i++];
            while (i < len && line[i] != '"')
                token[j++] = line[i++];
            if (i < len) token[j++] = line[i++]; // closing quote
            token[j] = '\0';
            process(token);
            continue;
        }

        // Handle symbols
        if (isSymbol(line[i])) {
            token[0] = line[i];
            token[1] = '\0';
            process(token);
            i++;
            continue;
        }

        // Handle operators (check 2-character ones first)
        if (strchr("=<>!&|", line[i])) {
            if (i + 1 < len && (line[i + 1] == '=' || line[i + 1] == line[i])) {
                token[0] = line[i];
                token[1] = line[i + 1];
                token[2] = '\0';
                i += 2;
            } else {
                token[0] = line[i];
                token[1] = '\0';
                i++;
            }
            process(token);
            continue;
        }

        // Handle identifiers and numbers
        j = 0;
        while (i < len && !isspace(line[i]) && !isSymbol(line[i]) && !strchr("=<>!&|\"", line[i])) {
            token[j++] = line[i++];
        }
        token[j] = '\0';
        if (strlen(token) > 0)
            process(token);
    }
}

void lexit() {
    FILE *fp = fopen("tem.txt", "r");
    if (!fp) {
        printf("Error: Could not open file.\n");
        return;
    }

    char line[300];
    while (fgets(line, sizeof(line), fp)) {
        tokenizeLine(line);
    }
    fclose(fp);
}

int main() {
    printf("Lexical Analysis Start\n\n");
    lexit();
    printf("\nLexical Analysis End\n");
    return 0;
}

*/