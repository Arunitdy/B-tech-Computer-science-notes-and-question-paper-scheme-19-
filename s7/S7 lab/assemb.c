#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void generateAssembly(char *lhs, char *op1, char *op, char *op2) {
   
    if (strcmp(op, "+") == 0) {
        printf("MOV R0, %s\n", op1);
        printf("ADD R0,  %s\n", op2);
        printf("MOv %s, R0\n", lhs);
    } else if (strcmp(op, "-") == 0) {
        printf("MOV R0, %s\n", op1);
        printf("SUB R0,  %s\n", op2);
        printf("MOv %s, R0\n", lhs);
    }  else if (strcmp(op, "*") == 0) {
        printf("MOV R0, %s\n", op1);
        printf("MUL R0,  %s\n", op2);
        printf("MOv %s, R0\n", lhs);
    }  else if (strcmp(op, "/") == 0) {
        printf("MOV R0, %s\n", op1);
        printf("DIV R0,  %s\n", op2);
        printf("MOv %s, R0\n", lhs);
    } else if (strcmp(op, "") == 0 && strcmp(op2, "") == 0) {
        printf("MOV %s, %s\n", lhs, op1);
    } else {
        printf("error conversion");
    }
    

}

int main() {
    printf("start \n");


    FILE *f1 = fopen("3ac.txt", "r");

    if (f1 == NULL) {
        printf("error opening");
        return 0;
    }
    char line[500];
    char lhs[100], op1[100], op[10], op2[100];


    while (fgets(line, sizeof(line), f1)) {
        printf("--------------------------------------------------");
        printf("\n%s\n", line);
        strcpy(lhs, ""); strcpy(op1, ""); strcpy(op, ""); strcpy(op2, "");
        if (sscanf(line, "%[^=]=%[^+-*/]%[+-*/]%s", lhs, op1, op, op2) == 4) {
            generateAssembly(lhs, op1, op, op2);
        } else if (sscanf(line, "%[^=]=%s", lhs, op1) == 2) {
            generateAssembly(lhs, op1, "", "");
        } else {
            printf("Invalid line format: %s", line);
            continue;
        }
        printf("--------------------------------------------------\n");
    }
    return 0;
}