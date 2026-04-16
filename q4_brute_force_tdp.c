#include <stdio.h>
#include <string.h>

char prod[20][20];
int n;
char input[100];
int len;

// Utility to find the start of RHS
int getRhs(char* p) {
    int i = 1;
    while(p[i] == '-' || p[i] == '>' || p[i] == '=') i++;
    return i;
}
int isEpsilon(char c) {
    return (c == 'e' || c == '#');
}

// Generic matching recursive function traversing all possibilities
int match(char nonterm, int idx, int *out_idx) {
    for (int i = 0; i < n; i++) {
        // Find matching production LHS
        if (prod[i][0] == nonterm) {
            int curr_idx = idx;
            int matched = 1;
            
            // Validate RHS
            int rhs = getRhs(prod[i]);
            for (int j = rhs; prod[i][j] != '\0'; j++) {
                char symbol = prod[i][j];
                if (symbol >= 'A' && symbol <= 'Z') {
                    int next_idx;
                    if (!match(symbol, curr_idx, &next_idx)) {
                        matched = 0; break;
                    }
                    curr_idx = next_idx;
                } else if (isEpsilon(symbol)) {
                    continue; // Epsilon production
                } else {
                    if (curr_idx < len && input[curr_idx] == symbol) {
                        curr_idx++;
                    } else {
                        matched = 0; break;
                    }
                }
            }
            if (matched) {
                *out_idx = curr_idx;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    printf("--- Brute Force Top Down Parsing ---\n");
    printf("Enter number of productions: ");
    scanf("%d", &n);
    
    printf("Enter productions (Format: 'S->aA', use 'e' for epsilon):\n");
    for (int i = 0; i < n; i++) scanf("%s", prod[i]);

    printf("Enter input string: ");
    scanf("%s", input);
    len = strlen(input);
    
    int end_idx;
    if (match(prod[0][0], 0, &end_idx) && end_idx == len) {
        printf("Result: String perfectly matches grammar (Accepted).\n");
    } else {
        printf("Result: String mismatch (Rejected).\n");
    }
    return 0;
}
