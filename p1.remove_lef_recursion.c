#include <stdio.h>
#include <string.h>

void main() {
    // prod = full input production, like A->Aa|b
    // alpha = stores recursive rules (Aa -> a), beta = non-recursive rules
    char prod[100], alpha[10][20], beta[10][20], nonTerminal;
    int i = 0, m = 0, n = 0;

    // ?? Step 1: Get user input
    printf("Enter production (e.g., A->Aa|b): ");
    scanf("%s", prod);  // Input like A->Aa|b

    // ?? Step 2: Extract non-terminal from LHS
    nonTerminal = prod[0];

    // Check format (must be like A->)
    if (!(prod[1] == '-' && prod[2] == '>')) {
        printf("Invalid production format!\n");
        return;
    }

    i = 3; // Start reading from RHS (skip A->)

    // Temporary string to hold each rule between '|'
    char temp[20];
    int t = 0;

    // ?? Step 3: Loop to split RHS rules by '|'
    while (1) {
        // End of one rule (either '|' or '\0')
        if (prod[i] == '|' || prod[i] == '\0') {
            temp[t] = '\0'; // End the string

            // If rule starts with nonTerminal ? it's left recursive
            if (temp[0] == nonTerminal)
                strcpy(alpha[m++], temp + 1);  // Remove nonTerminal and store in alpha[]
            else
                strcpy(beta[n++], temp);       // Store safe rules in beta[]

            t = 0; // Reset temp
            if (prod[i] == '\0') break; // End loop if end of string
        } else {
            temp[t++] = prod[i]; // Add character to temp rule
        }
        i++;
    }

    // ?? Step 4: If no left recursion found
    if (m == 0) {
        printf("No Left Recursion Detected.\n");
        return;
    }

    // ?? Step 5: Output new grammar after removing left recursion
    printf("After removing left recursion:\n");

    // Print: A -> beta A'
    printf("%c -> ", nonTerminal);
    for (i = 0; i < n; i++) {
        printf("%s%c'", beta[i], nonTerminal);  // Add A' to beta
        if (i != n - 1) printf(" | ");
    }

    // Print: A' -> alpha A' | e
    printf("\n%c' -> ", nonTerminal); // Proper A' (not B')
    for (i = 0; i < m; i++) {
        printf("%s%c' | ", alpha[i], nonTerminal); // alpha part + A'
    }
    printf("e\n");  // Always add epsilon (empty string) to end A' recursion
}
