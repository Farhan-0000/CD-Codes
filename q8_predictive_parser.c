#include <stdio.h>
#include <string.h>

char prod[20][20];
int n;
char input[100];
char stack[100];
int top = -1;

void push(char c) { stack[++top] = c; stack[top+1] = '\0'; }
char pop() { return top == -1 ? '\0' : stack[top--]; }

int getRhs(char* p) {
    int i = 1;
    while(p[i] == '-' || p[i] == '>' || p[i] == '=') i++;
    return i;
}
int isEpsilon(char c) {
    return (c == 'e' || c == '#');
}

// Simulates checking the standard LL(1) Predictive Parser Table dynamically
int getPredictiveRule(char nonterm, char lookahead) {
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == nonterm) {
            int rhs = getRhs(prod[i]);
            if (prod[i][rhs] == lookahead) return i;       // Terminal matches
            if (prod[i][rhs] >= 'A' && prod[i][rhs] <= 'Z') return i; // Assume non-terminal derivation path valid
            if (isEpsilon(prod[i][rhs])) return i;             // Epsilon derivation
        }
    }
    return -1;
}

int main() {
    printf("--- Predictive Parser validation ---\n");
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (Format S->aA): \n");
    for (int i = 0; i < n; i++) scanf("%s", prod[i]);

    printf("Enter input string (end with $): ");
    scanf("%s", input);

    push('$');
    push(prod[0][0]); // Start symbol
    int cursor = 0;

    printf("\n%-20s | %-20s | %s\n", "STACK", "INPUT", "ACTION");
    printf("--------------------------------------------------------------\n");
    
    while (stack[top] != '$' || input[cursor] != '$') {
        printf("%-20s | %-20s | ", stack, &input[cursor]);
        char X = stack[top];
        char a = input[cursor];

        if (X == a) {
            printf("Matched '%c'\n", a);
            pop(); cursor++;
            if (X == '$') break;
        } else if (X >= 'A' && X <= 'Z') {
            int ruleIdx = getPredictiveRule(X, a);
            if (ruleIdx != -1) {
                printf("Output Rule: %s\n", prod[ruleIdx]);
                pop();
                // Push RHS to stack in reverse
                int rhs_start = getRhs(prod[ruleIdx]);
                for (int k = strlen(prod[ruleIdx]) - 1; k >= rhs_start; k--) {
                    if (!isEpsilon(prod[ruleIdx][k])) push(prod[ruleIdx][k]);
                }
            } else {
                printf("Error: No predictive parsing rule found.\n");
                return 1;
            }
        } else {
            printf("Error: Mismatch detected for '%c' and '%c'.\n", X, a);
            return 1;
        }
    }
    
    printf("\nGiven String is VALID and successfully parsed by Predictive Parser.\n");
    return 0;
}
