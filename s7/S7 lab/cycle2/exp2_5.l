#include <stdio.h> 
#include <stdlib.h> 
int yylex(void); 
void yyerror(const char *s); 
%} 
%union { 
int num; 
} 
%token <num> NUMBER 
%type <num> expr 
%left '+' '-' 
%left '*' '/' 
%right UMINUS 
%% 
input: 
/* empty */ 
| input expr '\n' { printf("Valid expression, Result = %d\n", $2); } 
; 
expr: 
NUMBER 
| expr '+' expr { $$ = $1 + $3; } 
| expr '-' expr { $$ = $1 - $3; } 
| expr '*' expr { $$ = $1 * $3; } 
| expr '/' expr { 
if ($3 == 0) { 
yyerror("division by zero"); 
$$ = 0; 
} else { 
$$ = $1 / $3; 
} 
} 
| '(' expr ')' { $$ = $2; } 
| '-' expr %prec UMINUS { $$ = -$2; } 
; 
%% 
void yyerror(const char *s) { 
fprintf(stderr, "Error: %s\n", s); 
} 
int main() { 
printf("Enter arithmetic expressions (Ctrl+D to quit):\n"); 
yyparse(); 
return 0; 
} 
q5.l 
%{ 
#include "q5.tab.h" 
#include <stdlib.h> 
%} 
%% 
[0-9]+ { yylval.num = atoi(yytext); return NUMBER; } 
[ \t] ; // ignore whitespace 
\n return '\n'; 
. return yytext[0]; 
%% 
int yywrap() { return 1; } 