
#include <stdio.h> 
int lineCount = 0, wordCount = 0, charCount = 0; 
%} 
%option noyywrap 
%% 
\n { lineCount++; charCount++; } /* newline */ 
[ \t]+ { charCount += yyleng; } /* spaces/tabs */ 
[^ \t\n]+ { wordCount++; charCount += yyleng; } /* words */ 
%% 
int main(int argc, char *argv[]) 
{ 
if (argc > 1) 
{ 
FILE *file = fopen(argv[1], "r"); 
if (!file) 
{ 
printf("Error: Cannot open file %s\n", argv[1]); 
return 1; 
} 
yyin = file; 
} 
yylex(); 
printf("Lines: %d\nWords: %d\nCharacters: %d\n",lineCount, wordCount, charCount); 
return 0; 
}