#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][20];
int n;

// Utility to find the start of the Right-Hand Side (ignores -> or =)
int getRhs(char* p) {
    int i = 1;
    while(p[i] == '-' || p[i] == '>' || p[i] == '=') i++;
    return i;
}

// Utility to add uniquely into sets
void addToSet(char set[], char val) {
    if (val == 'e' || val == '#') return; // Handled explicitly in algorithm
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == val) return;
    }
    int len = strlen(set);
    set[len] = val;
    set[len + 1] = '\0';
}

int isEpsilon(char c) {
    return (c == 'e' || c == '#');
}

// Compute First Set for a Symbol dynamically
void findFirst(char symbol, char resultSet[]) {
    if (!(symbol >= 'A' && symbol <= 'Z')) { 
        if(!isEpsilon(symbol)) addToSet(resultSet, symbol); 
        return; 
    }
    for (int i = 0; i < n; i++) {
        if (prod[i][0] == symbol) {
            int rhs = getRhs(prod[i]);
            if (isEpsilon(prod[i][rhs])) {
                int len = strlen(resultSet);
                int hasEps = 0;
                for(int k=0; k<len; k++) if(isEpsilon(resultSet[k])) hasEps = 1;
                if(!hasEps) { resultSet[len] = '#'; resultSet[len+1] = '\0'; }
            } else {
                for (int j = rhs; prod[i][j] != '\0'; j++) {
                    char temp[20] = "";
                    findFirst(prod[i][j], temp);
                    int hasEps = 0;
                    for (int k = 0; temp[k] != '\0'; k++) {
                        if (isEpsilon(temp[k])) hasEps = 1;
                        else addToSet(resultSet, temp[k]);
                    }
                    if (!hasEps) break;
                    if (prod[i][j+1] == '\0') {
                        int len = strlen(resultSet);
                        int check = 0;
                        for(int k=0; k<len; k++) if(isEpsilon(resultSet[k])) check = 1;
                        if(!check) { resultSet[len] = '#'; resultSet[len+1] = '\0'; }
                    }
                }
            }
        }
    }
}

// Compute Follow Set for a Symbol dynamically
void findFollow(char symbol, char resultSet[]) {
    if (prod[0][0] == symbol) addToSet(resultSet, '$'); 
    
    for (int i = 0; i < n; i++) {
        int rhs = getRhs(prod[i]);
        for (int j = rhs; prod[i][j] != '\0'; j++) {
            if (prod[i][j] == symbol) {
                if (prod[i][j + 1] != '\0') {
                    char temp[20] = "";
                    int k = j + 1;
                    int hasEps = 1;
                    while(prod[i][k] != '\0' && hasEps) {
                        temp[0] = '\0';
                        findFirst(prod[i][k], temp);
                        hasEps = 0;
                        for (int m = 0; temp[m] != '\0'; m++) {
                            if (isEpsilon(temp[m])) hasEps = 1;
                            else addToSet(resultSet, temp[m]);
                        }
                        if (!hasEps) break;
                        k++;
                    }
                    if (prod[i][k] == '\0' && symbol != prod[i][0]) {
                        findFollow(prod[i][0], resultSet);
                    }
                }
                if (prod[i][j + 1] == '\0' && symbol != prod[i][0]) {
                    findFollow(prod[i][0], resultSet);
                }
            }
        }
    }
}

int main() {
    printf("--- First and Follow Sets ---\n");
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (Format: 'S->aA' or 'E=TR', use 'e' or '#' for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    printf("\nFIRST Sets:\n");
    char computed[256] = {0};
    for (int i = 0; i < n; i++) {
        char lhs = prod[i][0];
        if(!computed[(unsigned char)lhs]) {
            char resultSet[20] = "";
            findFirst(lhs, resultSet);
            for(int m=0; resultSet[m]; m++) if(resultSet[m] == '#') resultSet[m] = 'e';
            printf("FIRST(%c) = { %s }\n", lhs, resultSet);
            computed[(unsigned char)lhs] = 1;
        }
    }

    printf("\nFOLLOW Sets:\n");
    memset(computed, 0, 256);
    for (int i = 0; i < n; i++) {
        char lhs = prod[i][0];
        if(!computed[(unsigned char)lhs]) {
            char resultSet[20] = "";
            findFollow(lhs, resultSet);
            printf("FOLLOW(%c) = { %s }\n", lhs, resultSet);
            computed[(unsigned char)lhs] = 1;
        }
    }
    return 0;
}
