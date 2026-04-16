#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char str[100];
    printf("Enter a single token string to validate (simulate DFA): ");
    scanf("%s", str);

    int state = 0; 
    for (int i = 0; i < strlen(str); i++) {
        char c = str[i];
        
        // DFA Transitions
        if (state == 0) {
            if (isalpha(c) || c == '_') state = 1; // Valid Start for Identifier
            else if (isdigit(c)) state = 2;        // Valid Start for Number
            else state = 3;                        // Invalid State
        } else if (state == 1) {
            if (!isalnum(c) && c != '_') state = 3; 
        } else if (state == 2) {
            // Allowing simple decimals in numbers
            if (!isdigit(c) && c != '.') state = 3;
        }
    }
    
    // Check accepting states
    if (state == 1) {
        printf("Token is a Valid Identifier.\n");
    } else if (state == 2) {
        printf("Token is a Valid Number.\n");
    } else {
        printf("Token is Invalid.\n");
    }

    return 0;
}
