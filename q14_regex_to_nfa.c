#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dynamic Adjacency List Storage
typedef struct Node {
    int target_state;
    char transition;
    struct Node* next;
} Node;

Node* adjList[100];
int state_count = 0;

void addEdge(int u, int v, char symbol) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->target_state = v;
    newNode->transition = symbol;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}

int createState() {
    adjList[state_count] = NULL;
    return state_count++;
}

typedef struct {
    int start;
    int end;
} NFA;

NFA stack[100];
int top = -1;
void push(NFA n) { stack[++top] = n; }
NFA pop() { return stack[top--]; }

int main() {
    char postfix[100];
    printf("--- RegEx to e-NFA Engine (Thompson's Construction) ---\n");
    printf("Enter completely generated regex in POSTFIX string code (e.g. ab.|c*|): ");
    scanf("%s", postfix);

    for (int i=0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (c == '.' || c == '|' || c == '*') {
            if (c == '.') {
                NFA n2 = pop(), n1 = pop();
                addEdge(n1.end, n2.start, 'e'); // Concatenation specific bridge execution
                NFA n_new = {n1.start, n2.end};
                push(n_new);
            } else if (c == '|') {
                NFA n2 = pop(), n1 = pop();
                int sInit = createState();
                int sFinal = createState();
                addEdge(sInit, n1.start, 'e');
                addEdge(sInit, n2.start, 'e');
                addEdge(n1.end, sFinal, 'e');
                addEdge(n2.end, sFinal, 'e');
                NFA n_new = {sInit, sFinal};
                push(n_new);
            } else if (c == '*') {
                NFA n1 = pop();
                int sInit = createState();
                int sFinal = createState();
                addEdge(sInit, n1.start, 'e');
                addEdge(sInit, sFinal, 'e');
                addEdge(n1.end, n1.start, 'e');
                addEdge(n1.end, sFinal, 'e');
                NFA n_new = {sInit, sFinal};
                push(n_new);
            }
        } else {
            // Processing Standard Alphabetical Identifiers
            int s1 = createState();
            int s2 = createState();
            addEdge(s1, s2, c);
            NFA n_new = {s1, s2};
            push(n_new);
        }
    }
    
    NFA final_nfa = pop();
    printf("\nGenerated e-NFA Diagram Result utilizing Graph Structure:\n");
    printf(">> Initial State: q%d\n>> Goal State: q%d\n", final_nfa.start, final_nfa.end);
    printf("\nMapping Iterated Sub-routines:\n");
    for(int i = 0; i < state_count; i++) {
        Node* curr = adjList[i];
        while(curr != NULL) {
            printf("  State(q%d) --[%c]--> State(q%d)\n", i, curr->transition, curr->target_state);
            curr = curr->next;
        }
    }
    return 0;
}
