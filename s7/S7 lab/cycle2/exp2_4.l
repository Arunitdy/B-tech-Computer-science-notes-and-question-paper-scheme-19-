#include <stdio.h> 
#include <string.h> 
int vowelCount = 0, consonantCount = 0; 
char userInput[1024]; // renamed from 'input' 
%} 
%option noyywrap 
%% 
[aeiouAEIOU] { vowelCount++; } /* vowels */ 
[a-zA-Z] { consonantCount++; } /* consonants */ 
. { /* ignore other characters */ } 
\n { /* ignore newline */ } 
%% 
int main() { 
printf("Enter a string: "); 
fgets(userInput, sizeof(userInput), stdin); // read input from user 
// feed input to lexer 
YY_BUFFER_STATE bp = yy_scan_string(userInput); 
yylex(); 
yy_delete_buffer(bp); 
printf("Vowels: %d\nConsonants: %d\n", vowelCount, consonantCount); 
return 0; 
} 