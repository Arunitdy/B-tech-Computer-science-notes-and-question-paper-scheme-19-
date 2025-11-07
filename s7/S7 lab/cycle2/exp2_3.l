#include <stdio.h> 
%} 
%option noyywrap 
%% 
abc { printf("ABC"); } /* convert abc → ABC */ 
. { printf("%s", yytext); } /* print any other character */ 
\n { printf("\n"); } /* handle newline properly */ 
%% 
int main() { 
yylex(); 
return 0; 
} 