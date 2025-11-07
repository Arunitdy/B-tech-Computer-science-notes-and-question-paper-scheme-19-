#include <stdio.h> 
#include <string.h> 
int keywordCount = 0, idCount = 0, numCount = 0, opCount = 0, symCount = 0; 
%} 
%% 
"int"|"float"|"if"|"else"|"while"|"return" { 
printf("Keyword: %s\n", yytext); 
keywordCount++; 
} 
[a-zA-Z_][a-zA-Z0-9_]* { 
printf("Identifier: %s\n", yytext); 
idCount++; 
} 
[0-9]+ { 
printf("Number: %s\n", yytext); 
numCount++; 
} 
[+\-*/=<>] { 
printf("Operator: %s\n", yytext); 
opCount++; 
} 
[;,\(\)\{\}] { 
printf("Symbol: %s\n", yytext); 
symCount++; 
} 
[ \t\n]+ ; /* Ignore whitespace */ 
. { 
printf("Unknown: %s\n", yytext); 
} 
%% 
int main() { 
printf("Enter a program (Ctrl+D to finish):\n\n"); 
yylex(); 
return 0; 
} 
int yywrap() { 
return 1; 
} 