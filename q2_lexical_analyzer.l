%{
#include <stdio.h>
%}

%%
int|float|char|void|if|else|while|for|return|break|continue { printf("Keyword: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                                     { printf("Identifier: %s\n", yytext); }
[0-9]+(\.[0-9]+)?                                          { printf("Number: %s\n", yytext); }
[+\-*/%=]                                                 { printf("Operator: %s\n", yytext); }
[(){};,]                                                   { printf("Separator: %s\n", yytext); }
[ \t\n]+                                                   { /* Ignore whitespace */ }
.                                                          { printf("Unknown Token: %s\n", yytext); }
%%

int main() {
    printf("Enter string to analyze with Lex (Press Ctrl+D/Ctrl+Z to end):\n");
    yylex();
    return 0;
}

// Required for flex wrapper
int yywrap() { 
    return 1; 
}
