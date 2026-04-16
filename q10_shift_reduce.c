#include <stdio.h>
#include <string.h>

int n;
char prod[20][20];
char stack[100];
int top = -1;
char input[100];

void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void pop(int count) {
    top -= count;
    stack[top + 1] = '\0';
}

int getRhs(char* p) {
    int i = 1;
    while(p[i] == '-' || p[i] == '>' || p[i] == '=') i++;
    return i;
}

int main() {
    printf("--- Shift Reduce Parser using Stack ---\n");
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions:\n");
    for (int i = 0; i < n; i++) scanf("%s", prod[i]);

    printf("Enter input string: ");
    scanf("%s", input);

    int cursor = 0;
    int len = strlen(input);
    printf("\n%-20s | %-20s | %s\n", "STACK", "INPUT", "ACTION");
    printf("--------------------------------------------------------------\n");
    
    while(cursor < len || top >= 0) {
        printf("%-20s | %-20s | ", stack, &input[cursor]);
        
        int reduced = 0;
        // Verify stack top for a potential generic reduction
        for (int i = 0; i < n; i++) {
            int rhs_start = getRhs(prod[i]);
            int rhs_len = strlen(&prod[i][rhs_start]);
            if (top >= rhs_len - 1) {
                int match = 1;
                for (int j = 0; j < rhs_len; j++) {
                    if (stack[top - rhs_len + 1 + j] != prod[i][rhs_start + j]) { 
                        match = 0; 
                        break; 
                    }
                }
                if (match) {
                    pop(rhs_len);
                    push(prod[i][0]);
                    printf("REDUCE -> %s\n", prod[i]);
                    reduced = 1;
                    break;
                }
            }
        }
        
        // Push to stack memory
        if (!reduced) {
            if (cursor < len) {
                push(input[cursor++]);
                printf("SHIFT\n");
            } else {
                break;
            }
        }
    }
    
    if (top == 0 && stack[0] == prod[0][0] && cursor == len) {
        printf("\nResult: Parsing successful (Accepted).\n");
    } else {
        printf("\nResult: Syntax error occurred (Rejected).\n");
    }
    return 0;
}
