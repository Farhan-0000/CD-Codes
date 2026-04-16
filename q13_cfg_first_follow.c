#include <stdio.h>
#include <string.h>

// Full CFG storage structure encapsulating dynamic Left Recursion elimination
typedef struct {
    char lhs;
    char rhs[20];
} Production;

Production prod[40];
int num_prods = 0;

int getRhs(char* p) {
    int i = 1;
    while(p[i] == '-' || p[i] == '>' || p[i] == '=') i++;
    return i;
}
int isEpsilon(char c) {
    return (c == 'e' || c == '#');
}

// Central consistent algorithms
void eliminateLeftRecursion() {
    int original_num = num_prods;
    for (int i = 0; i < original_num; i++) {
        if (prod[i].lhs == prod[i].rhs[0]) {
            char A = prod[i].lhs;
            char beta[20] = "e";
            
            for (int k = 0; k < original_num; k++) {
                if (prod[k].lhs == A && prod[k].rhs[0] != A) {
                    strcpy(beta, prod[k].rhs);
                    prod[k].lhs = '#'; // Mark for deletion
                }
            }
            
            char alpha[20];
            strcpy(alpha, &prod[i].rhs[1]);
            prod[i].lhs = '#'; 
            
            char A_dash = A + 32; // Use lowercase instead of standard A' representation wrapper
            
            prod[num_prods].lhs = A;
            sprintf(prod[num_prods].rhs, "%s%c", strcmp(beta,"e")==0?"":beta, A_dash);
            num_prods++;
            
            prod[num_prods].lhs = A_dash;
            sprintf(prod[num_prods].rhs, "%s%c", alpha, A_dash);
            num_prods++;
            
            prod[num_prods].lhs = A_dash;
            strcpy(prod[num_prods].rhs, "e");
            num_prods++;
        }
    }
    
    // Compression cleanup targeting structurally marked indexes structure
    int j = 0;
    for(int i = 0; i < num_prods; i++) {
        if (prod[i].lhs != '#') prod[j++] = prod[i];
    }
    num_prods = j;
}

void addToSet(char set[], char val) {
    if (val == 'e') return;
    for (int i = 0; set[i] != '\0'; i++) if (set[i] == val) return;
    int len = strlen(set); set[len] = val; set[len + 1] = '\0';
}
void findFirst(char symbol, char resultSet[]) {
    // Dynamic mapping ignoring Non-Terms natively
    if (!(symbol >= 'A' && symbol <= 'Z')) { addToSet(resultSet, symbol); return; }
    for (int i = 0; i < num_prods; i++) {
        if (prod[i].lhs == symbol) {
            if (prod[i].rhs[0] == 'e' || prod[i].rhs[0] == '#') addToSet(resultSet, '#');
            else findFirst(prod[i].rhs[0], resultSet);
        }
    }
}
void findFollow(char symbol, char resultSet[]) {
    if (prod[0].lhs == symbol) addToSet(resultSet, '$'); 
    for (int i = 0; i < num_prods; i++) {
        for (int j = 0; prod[i].rhs[j] != '\0'; j++) {
            if (prod[i].rhs[j] == symbol) {
                if (prod[i].rhs[j + 1] != '\0') {
                    char nextSymbol = prod[i].rhs[j + 1];
                    char tempFirst[20] = "";
                    findFirst(nextSymbol, tempFirst);
                    for (int k = 0; tempFirst[k] != '\0'; k++) addToSet(resultSet, tempFirst[k]);
                }
                if (prod[i].rhs[j + 1] == '\0' && symbol != prod[i].lhs) {
                    findFollow(prod[i].lhs, resultSet);
                }
            }
        }
    }
}

int main() {
    printf("--- CFG Complete Toolset (Storage, LeftRecElimination, F&F) ---\n");
    printf("Enter number of initial explicit productions: ");
    scanf("%d", &num_prods);
    
    printf("Enter productions (Format S->aA):\n");
    for (int i = 0; i < num_prods; i++) {
        char temp[20];
        scanf("%s", temp);
        prod[i].lhs = temp[0];
        int rhs = getRhs(temp);
        strcpy(prod[i].rhs, &temp[rhs]);
    }

    eliminateLeftRecursion();

    printf("\nCleaned Left-Recursion Grammar:\n");
    for(int i = 0; i < num_prods; i++) {
        printf("%c->%s\n", prod[i].lhs, prod[i].rhs);
    }

    // Process & Output generated sets correctly
    printf("\nComputed FIRST Sets:\n");
    for (int i = 0; i < num_prods; i++) {
        char rs[20] = ""; 
        findFirst(prod[i].lhs, rs);
        printf("FIRST(%c) = { %s }\n", prod[i].lhs, rs);
    }
    
    printf("\nComputed FOLLOW Sets:\n");
    for (int i = 0; i < num_prods; i++) {
        char rs[20] = ""; 
        findFollow(prod[i].lhs, rs);
        printf("FOLLOW(%c) = { %s }\n", prod[i].lhs, rs);
    }
    return 0;
}
