#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char prod[20][20];
int n, cursor = 0;
char input[100];

// Utility functions for dynamic grammar scaling
int getRhs(char* p) {
    int i = 1;
    while(p[i] == '-' || p[i] == '>' || p[i] == '=') i++;
    return i;
}
int isEpsilon(char c) {
    return (c == 'e' || c == '#');
}

// Recursive parsing function dynamically exploring productions
int parse(char nonterm) {
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == nonterm) {
            int saved_cursor = cursor; // Backup cursor for explicit backtracking RDP support
            int success = 1;
            
            int rhs = getRhs(prod[i]);
            for (int j = rhs; prod[i][j] != '\0'; j++) {
                char sym = prod[i][j];
                
                if (sym >= 'A' && sym <= 'Z') {
                    if (!parse(sym)) { success = 0; break; }
                } else if (isEpsilon(sym)) {
                    continue;
                } else {
                    if (input[cursor] == sym) {
                        cursor++;
                    } else { 
                        success = 0; 
                        break; 
                    }
                }
            }
            if (success) return 1;
            cursor = saved_cursor; // Dynamic Backtrack if failed branch
        }
    }
    return 0;
}

int main() {
    printf("--- Dynamic Recursive Descent Parser ---\n");
    printf("Enter number of productions: ");
    scanf("%d", &n);
    
    printf("Enter productions (Format: 'E->T+E', start symbol must be first rule LHS):\n");
    for (int i = 0; i < n; i++) scanf("%s", prod[i]);
    
    printf("Enter input string: ");
    scanf("%s", input);

    if (parse(prod[0][0]) && input[cursor] == '\0') {
        printf("Result: Given String is Successfully Parsed!\n");
    } else {
        printf("Result: Parsing Failed. Given String does not match.\n");
    }
    return 0;
}
