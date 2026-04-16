#include <stdio.h>
#include <string.h>

int main() {
    int n;
    printf("--- Dynamic Code Generation Algorithm ---\n");
    printf("Enter number of Three Address Code statements: ");
    scanf("%d", &n);

    printf("Enter statements sequentially (Format 't1=A+B'):\n");
    
    // Parses incoming TAC formats into generalized Assembly code
    for (int i = 0; i < n; i++) {
        char stmt[30];
        scanf("%s", stmt);

        char res[10] = {0}, arg1[10] = {0}, op, arg2[10] = {0};
        int j = 0, k = 0;
        
        // Isolate Output Result Var
        while (stmt[j] != '=') res[k++] = stmt[j++];
        j++; k = 0;
        
        // Isolate Operand 1
        while (stmt[j] != '+' && stmt[j] != '-' && stmt[j] != '*' && stmt[j] != '/') {
            arg1[k++] = stmt[j++];
        }
        op = stmt[j++]; 
        k = 0;
        
        // Isolate Operand 2
        while (stmt[j] != '\0') arg2[k++] = stmt[j++];
        
        // Display matched mapping 
        printf("\nAssembly for [%s]:\n", stmt);
        printf("   MOV R0, %s\n", arg1);
        
        if (op == '+') printf("   ADD R0, %s\n", arg2);
        else if (op == '-') printf("   SUB R0, %s\n", arg2);
        else if (op == '*') printf("   MUL R0, %s\n", arg2);
        else if (op == '/') printf("   DIV R0, %s\n", arg2);
        
        printf("   MOV %s, R0\n", res);
    }
    printf("\nAssembly Code Generation Completed.\n");
    return 0;
}
