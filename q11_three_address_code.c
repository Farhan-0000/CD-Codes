#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Three Address Code (TAC) generation dynamically simulating C++ std::stack

int prec(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

// Custom Stack Implementation for specific datatypes used in TAC gen
char charStack[100];
int charTop = -1;
void pushChar(char c) { charStack[++charTop] = c; }
char popChar() { return charStack[charTop--]; }
char peekChar() { return charStack[charTop]; }
int isEmptyChar() { return charTop == -1; }

char strStack[100][10];
int strTop = -1;
void pushStr(const char* s) { strcpy(strStack[++strTop], s); }
char* popStr() { return strStack[strTop--]; }

int main() {
    char input[100];
    char post[100] = "";
    int pIdx = 0;
    
    printf("--- Three Address Code Generator (Dynamic) ---\n");
    printf("Enter standard infix expression (e.g. a+b*c): ");
    scanf("%s", input);

    // 1. Shunting-Yard: Infix -> Postfix implementation 
    for (int i = 0; input[i] != '\0'; i++) {
        char c = input[i];
        if (isalnum(c)) {
            post[pIdx++] = c;
        } else if (c == '(') {
            pushChar(c);
        } else if (c == ')') {
            while (!isEmptyChar() && peekChar() != '(') post[pIdx++] = popChar();
            popChar(); // Remove '('
        } else {
            while (!isEmptyChar() && prec(peekChar()) >= prec(c)) {
                post[pIdx++] = popChar();
            }
            pushChar(c);
        }
    }
    while (!isEmptyChar()) post[pIdx++] = popChar();
    post[pIdx] = '\0';

    printf("\nIntermediate Postfix output: %s\n\nGenerated Three Address Code:\n", post);

    // 2. Compute TAC from generating Temporary Variables (t1, t2 ...) based on Postfix
    int t = 1;
    for (int i = 0; post[i] != '\0'; i++) {
        char c = post[i];
        if (isalnum(c)) {
            char temp[2] = {c, '\0'};
            pushStr(temp);
        } else {
            char r[10], l[10];
            strcpy(r, popStr());
            strcpy(l, popStr());
            
            char res[10];
            sprintf(res, "t%d", t++);
            
            printf("%s = %s %c %s\n", res, l, c, r);
            pushStr(res);
        }
    }
    return 0;
}
