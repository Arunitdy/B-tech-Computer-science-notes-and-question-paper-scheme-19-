#include <stdio.h> 
#include <stdlib.h> 
int yylex(); 
void yyerror(const char *s); 
%} 
%token IDENTIFIER 
%% 
input: 
IDENTIFIER '\n' { printf("Valid identifier!\n"); } 
| error '\n' { printf("Invalid identifier!\n"); yyclearin; } 
; 
%% 
void yyerror(const char *s) { 
fprintf(stderr, "Error: %s\n", s); 
} 
int main() { 
printf("Enter an identifier: "); 
yyparse(); 
return 0; 
} 
id.l 
%{ 
#include "id.tab.h" /* or "y.tab.h" depending on your system */ 
%} 
%% 
[a-zA-Z][a-zA-Z0-9]* { return IDENTIFIER; } 
\n { return '\n'; } 
. { return yytext[0]; } 
%% 
int yywrap() { return 1; }