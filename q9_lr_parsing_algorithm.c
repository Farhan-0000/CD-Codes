#include <stdio.h>
#include <string.h>

int n;
char prod[20][20];
char stack[100];
int top = -1;
char input[100];

void push(char c) { stack[++top] = c; stack[top + 1] = '\0'; }
void pop(int count) { top -= count; stack[top + 1] = '\0'; }

int getRhs(char* p) {
    int i = 1;
    while(p[i] == '-' || p[i] == '>' || p[i] == '=') i++;
    return i;
}

int main() {
    printf("--- LR Parsing Algorithm Simulation ---\n");
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions:\n");
    for (int i = 0; i < n; i++) scanf("%s", prod[i]);

    printf("Enter input string: ");
    scanf("%s", input);

    int cursor = 0;
    int len = strlen(input);
    printf("\n%-20s | %-20s | %s\n", "STACK", "INPUT", "LR ACTION");
    printf("--------------------------------------------------------------\n");
    
    // LR Simulation loop using Shift-Reduce structural model
    while(cursor < len || top >= 0) {
        printf("%-20s | %-20s | ", stack, &input[cursor]);
        
        // Attempt Handle Reduction (LR Reduce phase evaluation)
        int reduced = 0;
        for (int i = 0; i < n; i++) {
            int rhs_start = getRhs(prod[i]);
            int rhs_len = strlen(&prod[i][rhs_start]);
            if (top >= rhs_len - 1) {
                int match = 1;
                for (int j = 0; j < rhs_len; j++) {
                    if (stack[top - rhs_len + 1 + j] != prod[i][rhs_start + j]) { 
                        match = 0; break; 
                    }
                }
                if (match) {
                    pop(rhs_len);
                    push(prod[i][0]);
                    printf("LR REDUCE via %s\n", prod[i]);
                    reduced = 1;
                    break;
                }
            }
        }
        
        // Proceed with LR Shift action if no reductions matched
        if (!reduced) {
            if (cursor < len) {
                push(input[cursor++]);
                printf("LR SHIFT\n");
            } else {
                break;
            }
        }
    }
    
    if (top == 0 && stack[0] == prod[0][0] && cursor == len) {
        printf("\nResult: String ACCEPTED according to LR parsing structure.\n");
    } else {
        printf("\nResult: String REJECTED.\n");
    }
    return 0;
}
