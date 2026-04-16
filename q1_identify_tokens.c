#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Helper to check if a string is a standard C keyword
int isKeyword(char buffer[]) {
    char keywords[16][10] = {"int", "float", "char", "double", "while", "for", "if", "else", 
                             "return", "void", "do", "switch", "case", "break", "continue", "default"};
    for(int i = 0; i < 16; ++i) {
        if(strcmp(keywords[i], buffer) == 0) return 1;
    }
    return 0;
}

int main() {
    char c, buffer[50];
    int j = 0;
    
    printf("Enter code string (end with $):\n");
    
    while((c = getchar()) != '$') {
        if(isalnum(c) || c == '_') {
            buffer[j++] = c;
        } else {
            if(j > 0) {
                buffer[j] = '\0';
                if(isKeyword(buffer)) printf("Keyword: %s\n", buffer);
                else if(isdigit(buffer[0])) printf("Number: %s\n", buffer);
                else printf("Identifier: %s\n", buffer);
                j = 0;
            }
            // Check for operators and separators 
            if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=') 
                printf("Operator: %c\n", c);
            else if(c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}') 
                printf("Separator: %c\n", c);
        }
    }
    return 0;
}
