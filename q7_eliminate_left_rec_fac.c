#include <stdio.h>
#include <string.h>

int getRhs(char* p) {
    int i = 1;
    while(p[i] == '-' || p[i] == '>' || p[i] == '=') i++;
    return i;
}

int main() {
    char prod[20], alpha[20], beta[20], gamma[20];
    int n;
    printf("--- Left Recursion & Left Factoring Elimination ---\n");
    printf("Enter Number of Productions: ");
    scanf("%d", &n);
    printf("Format Rule:\nLeft Recursion: 'A->Aalpha|beta'\nLeft Factoring: 'A->aBeta|aGamma'\n\n");
    
    for(int i = 0; i < n; i++) {
        printf("Enter production %d: ", i + 1);
        scanf("%s", prod);
        
        int rhs = getRhs(prod);
        
        // Dynamic Left Recursion check (Direct only)
        if(prod[0] == prod[rhs]) {
            int j = rhs + 1, k = 0;
            while(prod[j] != '|') alpha[k++] = prod[j++];
            alpha[k] = '\0'; 
            j++; k = 0;
            while(prod[j] != '\0') beta[k++] = prod[j++];
            beta[k] = '\0';
            
            printf(">> Left Recursion Detected & Eliminated:\n");
            printf("   %c->%s%c'\n", prod[0], beta, prod[0]);
            printf("   %c'->%s%c'|e\n\n", prod[0], alpha, prod[0]);
        } else {
            // Dynamic Left Factoring check (Matches immediate first symbol)
            int isFactored = 0;
            for (int k = rhs; prod[k] != '\0'; k++) {
                if (prod[k] == '|') {
                    if (prod[rhs] == prod[k + 1]) { // Common prefix
                        printf(">> Left Factoring Detected & Eliminated:\n");
                        int bR = rhs + 1, cR = k + 2, x = 0;
                        while(prod[bR] != '|') { 
                            beta[x++] = prod[bR++]; 
                            if(bR >= k) break;
                        } 
                        beta[x] = '\0';
                        
                        x = 0;
                        while(prod[cR] != '\0') gamma[x++] = prod[cR++]; 
                        gamma[x] = '\0';
                        
                        printf("   %c->%c%c'\n", prod[0], prod[rhs], prod[0]);
                        printf("   %c'->%s|%s\n\n", prod[0], beta[0] ? beta : "e", gamma[0] ? gamma : "e");
                        isFactored = 1;
                        break;
                    }
                }
            }
            if(!isFactored && prod[0] != prod[rhs]) {
                printf(">> No standard Left Recursion or Factoring strictly present for: %s\n\n", prod);
            }
        }
    }
    return 0;
}
