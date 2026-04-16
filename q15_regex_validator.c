#include <stdio.h>
#include <string.h>
#include <ctype.h>

int precedence(char c) {
    if (c == '*') return 3;
    if (c == '.') return 2;
    if (c == '|') return 1;
    return 0;
}

// Subcomponent: Infix (Standard string code format) -> Postfix 
void regToPostfix(char* infix, char* postfix) {
    char stack[100];
    int top = -1, pIdx = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (isalnum(c)) {
            postfix[pIdx++] = c;
        } else if (c == '(') {
            stack[++top] = c;
        } else if (c == ')') {
            while (top >= 0 && stack[top] != '(') postfix[pIdx++] = stack[top--];
            if (top >= 0) top--; // Pop parenthetical structure element
        } else {
            while (top >= 0 && stack[top] != '(' && precedence(stack[top]) >= precedence(c)) {
                postfix[pIdx++] = stack[top--];
            }
            stack[++top] = c;
        }
    }
    while (top >= 0) postfix[pIdx++] = stack[top--];
    postfix[pIdx] = '\0';
}

// Algorithm to recursively map valid strings inside equivalent state representation evaluation
int recursiveMatch(char* regex, int rIdx, char* str, int sIdx) {
    if (regex[rIdx] == '\0' && str[sIdx] == '\0') return 1;
    if (regex[rIdx] == '\0') return 0;

    // Resolve '*' dynamic string operator map evaluation logic
    if (regex[rIdx + 1] == '*') {
        if (recursiveMatch(regex, rIdx + 2, str, sIdx)) return 1;
        if (str[sIdx] != '\0' && (regex[rIdx] == str[sIdx])) {
            return recursiveMatch(regex, rIdx, str, sIdx + 1);
        }
        return 0;
    }

    if (regex[rIdx] == '.') {
        return recursiveMatch(regex, rIdx + 1, str, sIdx); // Skip concat operator without consuming character
    }

    if (str[sIdx] != '\0' && regex[rIdx] == str[sIdx]) {
        return recursiveMatch(regex, rIdx + 1, str, sIdx + 1);
    }
    return 0; // Return execution mismatch natively mapped
}

int main() {
    char infix[100], postfix[100], input[100];
    
    printf("--- Evaluator for RegEx Expression Rulesets ---\n");
    printf("Format Rules:\n");
    printf("Use explicit '.' struct operators for concatenation mapping (E.g. a.b.c|e*):\n> ");
    scanf("%s", infix);

    regToPostfix(infix, postfix);
    printf(">> Executing dynamic Postfix resolution valid output context map: %s\n", postfix);

    printf("\nEnter String target mapping validator context: ");
    scanf("%s", input);

    if (recursiveMatch(infix, 0, input, 0)) {
        printf("\nRESULT -> [True] The identified string dynamically explicitly perfectly matched!\n");
    } else {
        printf("\nRESULT -> [False] String structurally mismatches execution states internally.\n");
    }
    
    return 0;
}
